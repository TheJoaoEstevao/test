/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:13 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 15:19:32 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static t_bool	ft_check_newline_flag(char *cmd)
{
	int	i;

	i = 2;
	if (!cmd)
		return (FALSE);
	if (!ft_strncmp(cmd, "-n", 2))
	{
		while (cmd[i])
		{
			if (cmd[i++] != 'n')
				return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}

int	ft_echo(char **cmds)
{
	int		i;
	t_bool	newline;

	i = 1;
	newline = TRUE;
	while (cmds[i] && ft_check_newline_flag(cmds[i]))
	{
		newline = FALSE;
		i++;
	}
	while (cmds[i])
	{
		ft_putstr_fd(cmds[i], 1);
		if (cmds[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
