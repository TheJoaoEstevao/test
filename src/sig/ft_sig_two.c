/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:33 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:51:34 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

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
		write(1, "\n", 1);
	else if (ms->code == 131)
		write(1, "Quit: (core dumped)\n", 20);
}

void	ft_handle_hdoc_signal(int signo)
{
	int	fd;

	fd = 0;
	if (signo == SIGINT)
	{
		g_signo = 130;
		fd = open(TEMP_NFS, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd, 0);
		ft_close(fd);
		ioctl(0, TIOCSTI, "\n");
	}
}
