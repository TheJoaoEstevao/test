/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:16 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:51:17 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_bool	ft_check_adjacent_pipes(char *str)
{
	int		i;
	char	last_op;

	i = -1;
	last_op = 0;
	while (str[++i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if (last_op)
				return (TRUE);
			last_op = str[i];
		}
		else if (!ft_isspace(str[i]))
			last_op = 0;
	}
	return (last_op != 0);
}

void	ft_handle_pipe_child(t_ms *ms)
{
	g_signo = 0;
	signal(SIGINT, ft_handle_hdoc_signal);
	ft_bzero(ms->track, sizeof(t_track));
	ft_hdoc_child(ms);
}

t_bool	ft_is_leading_pipe(char *str)
{
	char	*first_pipe;
	char	*next_pipe;

	first_pipe = ft_strstr(str, "|");
	if (!first_pipe || first_pipe != str)
		return (FALSE);
	next_pipe = ft_strstr(first_pipe + 1, "|");
	return (!next_pipe);
}

t_bool	ft_has_consecutive_pipes(char *str)
{
	int	pipe_count;

	pipe_count = 0;
	while (*str)
	{
		if (*str == '|')
		{
			pipe_count++;
			if (pipe_count > 1)
				return (TRUE);
		}
		else if (!ft_isspace(*str))
			pipe_count = 0;
		str++;
	}
	return (FALSE);
}
