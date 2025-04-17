/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:13 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:50:14 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static t_bool	ft_check_newline_flag(char *cmd)
{
	int	index;

	index = 2;
	if (!cmd)
		return (FALSE);
	if (!ft_strncmp(cmd, "-n", 2))
	{
		while (cmd[index])
		{
			if (cmd[index++] != 'n')
				return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}

int	ft_echo(char **cmds)
{
	int		index;
	t_bool	newline;

	index = 1;
	newline = TRUE;
	while (cmds[index] && ft_check_newline_flag(cmds[index]))
	{
		newline = FALSE;
		index++;
	}
	while (cmds[index])
	{
		ft_putstr_fd(cmds[index], 1);
		if (cmds[index + 1])
			write(1, " ", 1);
		index++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
