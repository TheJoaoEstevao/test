/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:18 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 15:39:10 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_process_hdoc_line(t_ms *sh, char **arg_i)
{
	sh->track->i = -1;
	if (sh->doc_state != 1)
	{
		while ((*arg_i)[++sh->track->i])
		{
			if ((*arg_i)[sh->track->i] == '$')
			{
				ft_expand_hdoc_vars(sh, *arg_i - 1, arg_i);
				break ;
			}
		}
	}
	ft_putendl_fd(*arg_i, sh->track->arg_i);
	free(*arg_i);
}

static int	ft_process_heredoc_line(t_token *heredoc, t_ms *ms, char *arg_i)
{
	if (g_signo == 130)
		return (1);
	if (!arg_i)
	{
		ft_putstr_fd(HDOC_EOF_WARN, 1);
		ft_putstr_fd(" `", 1);
		ft_putstr_fd(heredoc->limit, 1);
		ft_putendl_fd("`)", 1);
		return (1);
	}
	ms->line_count++;
	if (ft_is_str_equal(arg_i, heredoc->limit))
	{
		free(arg_i);
		return (1);
	}
	ft_process_hdoc_line(ms, &arg_i);
	return (0);
}

static void	ft_heredoc(t_token *heredoc, t_ms *ms)
{
	char	*arg_i;

	arg_i = NULL;
	ms->track->arg_i = open(ms->cache, O_RDWR | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, ft_handle_hdoc_signal);
	while (g_signo != 130)
	{
		arg_i = readline("> ");
		if (ft_process_heredoc_line(heredoc, ms, arg_i))
			break ;
	}
	ft_close(ms->track->arg_i);
	if (g_signo != 130)
		ms->in_fd = open(ms->cache, O_RDONLY);
}

static void	ft_handle_hdoc_child(t_token *heredoc_node, t_ms *ms)
{
	g_signo = 0;
	ft_heredoc(heredoc_node, ms);
	ft_close(0);
	unlink(TEMP);
	ft_free_token_list(heredoc_node);
	ms->doc_list = NULL;
	rl_clear_history();
	ft_cleanup_shell(ms);
	if (g_signo == 130)
		exit(2);
	exit(0);
}

void	ft_create_heredoc(t_token *heredoc_node, t_ms *ms)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		ft_handle_hdoc_child(heredoc_node, ms);
	else
	{
		waitpid(pid, &status, 0);
		ft_setup_signals();
		if (status > 128)
		{
			ft_putchar_fd('\n', 1);
			ms->code = 130;
			ft_free_token_list(ms->doc_list);
			ms->doc_list = NULL;
			ft_cleanup_heredoc(ms);
			ft_reset_shell_state(ms);
		}
	}
}
