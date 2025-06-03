/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:31 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 10:28:58 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_signal_refresh(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handle_child_signal(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
		g_signo = 128 + signo;
}

void	ft_setup_signals(void)
{
	signal(SIGINT, ft_signal_refresh);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_update_exit_status(t_ms *ms, int status)
{
	g_signo = 0;
	if (WTERMSIG(status))
		ms->code = 128 + WTERMSIG(status);
	else if (WEXITSTATUS(status) == 13 || WEXITSTATUS(status) == 20)
		ms->code = 126;
	else if (WEXITSTATUS(status) == 3)
		ms->code = 127;
	else if (WEXITSTATUS(status) == 1 || WEXITSTATUS(status) == 4)
		ms->code = 1;
	else if (WEXITSTATUS(status) == 21)
		ms->code = 126;
	else
		ms->code = WEXITSTATUS(status);
	if (ms->code == 130)
		ft_putchar_fd('\n', 1);
	else if (ms->code == 131)
		ft_putendl_fd("Quit: (core dumped)", 1);
}

void	ft_handle_hdoc_signal(int signo)
{
	int	fd;

	fd = 0;
	if (signo == SIGINT)
	{
		g_signo = 130;
		fd = open(TEMP, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd, 0);
		ft_close(fd);
		ioctl(0, TIOCSTI, "\n");
	}
}
