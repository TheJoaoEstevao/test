/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:46 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 15:41:48 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_bool	ft_check_cmd(t_ms *ms, char **cmds)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (ft_is_str_equal(cmds[0], "export"))
		return (TRUE);
	if (ft_is_absolute_path(cmds[0]))
	{
		cmd_path = ft_strdup(cmds[0]);
		if (!chdir(cmds[0]))
			ft_cmd_error_exit(ms, cmds[0], 21, cmd_path);
	}
	else if (cmds[0][0])
		cmd_path = ft_find_cmd_path(cmds[0], ms);
	if (!cmd_path)
		return (FALSE);
	else
		free(cmd_path);
	return (TRUE);
}

static void	ft_handle_path_error(t_ms *ms, char **cmds, char *cmd_path)
{
	if (cmd_path == NULL)
	{
		if (!ft_is_present(cmds[0], '/'))
		{
			ft_putstr_fd("[minishell]: ", 2);
			ft_putstr_fd(cmds[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_cleanup_and_exit(ms, 127);
			exit(127);
		}
		ft_handle_null_path(ms, cmds);
	}
	execve(cmd_path, cmds, ms->current);
	if (errno == ENOEXEC)
	{
		ft_putstr_fd("[minishell]: ", 2);
		ft_putstr_fd(cmds[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_cleanup_and_exit(ms, 2);
		exit(126);
	}
	perror("[minishell]");
	exit(1);
}

void	ft_execute_cmd(t_ms *ms, char **cmds)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (ft_is_absolute_path(cmds[0]))
	{
		cmd_path = ft_strdup(cmds[0]);
		if (!chdir(cmds[0]))
			ft_cmd_error_exit(ms, cmds[0], 21, cmd_path);
	}
	else if (cmds[0][0])
		cmd_path = ft_find_cmd_path(cmds[0], ms);
	ft_handle_path_error(ms, cmds, cmd_path);
}

static void	ft_process_redirection(t_ms *ms, t_cmd *node, t_token *temp)
{
	int	flags;

	if (ft_check_input_redirection(ms, temp))
	{
		if (node->cmds && ft_check_cmd(ms, node->cmds))
			dup2(ms->in_fd, STDIN_FILENO);
		ft_close(ms->in_fd);
	}
	else if (temp->t_type == TOK_RED_OUT || temp->t_type == TOK_APPEND)
	{
		flags = O_TRUNC;
		if (temp->t_type == TOK_APPEND)
			flags = O_APPEND;
		ms->out_fd = open(temp->content, O_WRONLY | O_CREAT | flags, 0644);
		if (node->cmds && ft_check_cmd(ms, node->cmds))
			dup2(ms->out_fd, STDOUT_FILENO);
		ft_close(ms->out_fd);
	}
}

void	ft_handle_redirections(t_ms *ms, t_cmd *node)
{
	t_token	*temp;

	temp = node->io;
	while (temp)
	{
		ft_rm_quotes_hdoc(temp->content);
		if (temp->t_type == TOK_RED_IN && access(temp->content, F_OK))
		{
			ft_putstr_fd("[minishell]: ", 2);
			perror(temp->content);
			ft_cleanup_and_exit(ms, 1);
		}
		if (temp->t_type != TOK_RED_IN && !access(temp->content, F_OK)
			&& access(temp->content, W_OK))
		{
			ft_putstr_fd("[minishell]: ", 2);
			ft_putstr_fd(temp->content, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			ft_cleanup_and_exit(ms, 1);
		}
		ft_process_redirection(ms, node, temp);
		temp = temp->next;
	}
}
