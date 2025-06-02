/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:13 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 12:45:15 by jestevao         ###   ########.fr       */
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
			ft_putchar_fd(' ', 1);
		index++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
