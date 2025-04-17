/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:49 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:50:50 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_child_continue(t_ms *ms, t_cmd *node)
{
	ft_handle_redirections(ms, node);
	if (ft_is_child(node->cmds))
	{
		ms->code = ft_route(ms, node->cmds);
		ft_cleanup_and_exit(ms, ms->code);
	}
	else if (node->cmds && node->cmds[0])
	{
		ft_close_pipes(ms);
		ft_execute_command(ms, node->cmds);
	}
	ft_cleanup_and_exit(ms, 0);
}

static void	ft_child_process(t_ms *ms, t_cmd *node)
{
	signal(SIGINT, ft_handle_child_signal);
	signal(SIGQUIT, ft_handle_child_signal);
	if (ft_is_parent(node->cmds))
	{
		ft_close_pipes(ms);
		ft_cleanup_shell(ms);
		exit(0);
	}
	if (node->cmds && ms->in_fd != STDIN_FILENO && \
		ft_check_command(ms, node->cmds))
	{
		dup2(ms->in_fd, STDIN_FILENO);
		ft_close(ms->in_fd);
	}
	if (node->cmds && ms->out_fd != STDOUT_FILENO && \
		ft_check_command(ms, node->cmds))
	{
		dup2(ms->out_fd, STDOUT_FILENO);
		ft_close(ms->out_fd);
	}
	ft_child_continue(ms, node);
}

static void	ft_end_parent(t_ms *ms, int i)
{
	if (i == ms->exec_num - 1)
	{
		while (i-- >= 0)
			waitpid(0, NULL, 0);
	}
	ft_cleanup_heredoc(ms);
	ft_setup_signals();
}

static void	ft_parent_process(t_ms *ms, t_cmd *node, int *status, int i)
{
	if (ft_is_parent(node->cmds) && ms->exec_num == 1)
	{
		ms->code = ft_route(ms, node->cmds);
		ft_close_pipes(ms);
		ft_setup_signals();
		ft_cleanup_heredoc(ms);
		ft_reset_shell_state(ms);
	}
	else if (i == ms->exec_num - 1)
	{
		ft_close_pipes(ms);
		waitpid(ms->process, status, 0);
		ft_update_exit_status(ms, *status);
	}
	if (ms->in_fd != STDIN_FILENO)
		ft_close(ms->in_fd);
	if (i < ms->exec_num - 1)
		ft_close(ms->channels[i][1]);
	if (ms->exec_num > 1)
		ms->in_fd = ms->channels[i][0];
}

void	ft_executor(t_ms *ms, t_cmd *parser, int i)
{
	t_cmd		*node;
	int			status;

	status = 0;
	node = parser;
	if (node->mode == TOK_PIPE)
		node = parser->left;
	if (i == ms->exec_num - 1)
		ms->out_fd = STDOUT_FILENO;
	else
		ms->out_fd = ms->channels[i][1];
	ft_expand_commands(&node->cmds, ms);
	signal(SIGINT, SIG_IGN);
	ms->process = fork();
	if (ms->process == 0)
		ft_child_process(ms, node);
	else
	{
		ft_parent_process(ms, node, &status, i);
		if (parser->mode == TOK_PIPE)
			ft_executor(ms, parser->right, ++i);
	}
	ft_end_parent(ms, i);
}
