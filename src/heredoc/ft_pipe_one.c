/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:13 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:51:14 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_hdoc_child(t_ms *ms)
{
	int		fd;
	char	*line;

	fd = open(".tempstr", O_RDWR | O_CREAT, 0644);
	line = readline("> ");
	if (!line && g_signo != 130)
		ft_handle_heredoc_eof(ms, fd);
	while (g_signo != 130 && ft_is_empty_line(line))
	{
		free(line);
		line = readline("> ");
		if (!line && g_signo != 130)
			ft_handle_heredoc_eof(ms, fd);
	}
	if (g_signo != 130)
		ft_putstr_fd(line, fd);
	free(line);
	ft_close(fd);
	ft_close(0);
	unlink(TEMP_NFS);
	ft_cleanup_shell(ms);
	if (g_signo == 130)
		exit(2);
	exit(0);
}

static int	ft_process_hdoc_temp(t_ms *ms, int status)
{
	int		fd;
	char	*tempstr;
	char	*old_buff;

	fd = open(".tempstr", O_RDWR);
	if (fd == -1)
		return (status);
	tempstr = ft_gnl(fd);
	ft_close(fd);
	unlink(".tempstr");
	if (tempstr)
	{
		ft_check_pipe_syntax(ms, tempstr);
		if (WEXITSTATUS(status) != 3)
		{
			old_buff = ms->buff;
			ms->buff = ft_nl_strjoin(ms->buff, tempstr);
			free(old_buff);
		}
		free(tempstr);
	}
	return (status);
}

static int	ft_heredoc_parent(t_ms *ms, pid_t pid)
{
	int		status;

	waitpid(pid, &status, 0);
	ft_setup_signals();
	if (status == 512)
	{
		write(1, "\n", 1);
		ms->code = 130;
		unlink(".tempstr");
		return (ft_reset_shell_state(ms), status);
	}
	return (ft_process_hdoc_temp(ms, status));
}

static char	*ft_handle_pipe_loop(t_ms *ms, char *trimmed)
{
	pid_t	pid;

	while (trimmed[ft_strlen(trimmed) - 1] == '|')
	{
		free(trimmed);
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			ft_handle_pipe_child(ms);
		else if (ft_heredoc_parent(ms, pid) == 768)
		{
			ft_cleanup_shell(ms);
			exit(2);
		}
		trimmed = ft_strtrim(ms->buff, DELIMS);
	}
	free(trimmed);
	return (ms->buff);
}

char	*ft_open_pipe(t_ms *ms)
{
	char	*trimmed;

	trimmed = ft_strtrim(ms->buff, DELIMS);
	if (!trimmed)
		return (ms->buff);
	if (ft_check_pipe_syntax(ms, trimmed))
		return (free(trimmed), ms->buff);
	if ((ft_check_adjacent_pipes(trimmed) || ft_has_consecutive_pipes(trimmed)) \
		|| ft_is_leading_pipe(trimmed))
		return (free(trimmed), ms->buff);
	return (ft_handle_pipe_loop(ms, trimmed));
}
