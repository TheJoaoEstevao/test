/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:54 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 12:50:29 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_cmd_not_found(t_ms *ms, const char *cmd)
{
	ft_putstr_fd("[minishell]: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	rl_clear_history();
	ft_cleanup_and_exit(ms, 127);
	exit(127);
}

void	ft_cmd_not_exist(t_ms *ms, const char *cmd, int err_no, char *path)
{
	if (path)
		free(path);
	ft_putstr_fd("[minishell]: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(err_no), 2);
	ft_putstr_fd("\n", 2);
	ft_close_pipes(ms);
	if (ms->in_fd != STDIN_FILENO)
		ft_close(ms->in_fd);
	if (ms->out_fd != STDOUT_FILENO)
		ft_close(ms->out_fd);
	rl_clear_history();
	if (err_no == 13)
		ft_cleanup_and_exit(ms, 126);
	if (err_no == 2)
		ft_cleanup_and_exit(ms, 127);
	ft_cleanup_and_exit(ms, err_no);
}

void	ft_create_pipes(t_ms *ms)
{
	int	i;

	i = -1;
	if (ms->exec_num > 1)
	{
		ms->channels = ft_calloc(ms->exec_num, sizeof(int *));
		while (++i < ms->exec_num)
		{
			ms->channels[i] = malloc(sizeof(int) * 2);
			if (pipe(ms->channels[i]) == -1)
			{
				perror("pipe_creation");
				exit(1);
			}
		}
	}
}

void	ft_close_pipes(t_ms *ms)
{
	int	i;

	i = -1;
	if (ms->exec_num > 1)
	{
		while (++i <= ms->exec_num - 1)
		{
			if (ms->channels[i][0] > 2)
				ft_close(ms->channels[i][0]);
			if (ms->channels[i][1] > 2)
				ft_close(ms->channels[i][1]);
		}
	}
}

int	ft_check_input_redirection(t_ms *ms, t_token *temp)
{
	if (temp->kind == TOK_RED_IN || temp->kind == TOK_HEREDOC)
	{
		if (temp->kind == TOK_HEREDOC)
			ms->in_fd = open(ms->cache, O_RDONLY);
		else
			ms->in_fd = open(temp->content, O_RDONLY);
		if (ms->in_fd < 0)
		{
			ft_putstr_fd("[minishell]: ", 2);
			perror(temp->content);
			ft_cleanup_and_exit(ms, 1);
		}
		return (1);
	}
	return (0);
}
