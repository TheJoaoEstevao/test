/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:25 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 17:16:30 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_bool	ft_is_child(char **cmds)
{
	if (!cmds || !cmds[0])
		return (FALSE);
	if (ft_is_str_equal(cmds[0], "echo"))
		return (TRUE);
	if (ft_is_str_equal(cmds[0], "env"))
		return (TRUE);
	if (ft_is_str_equal(cmds[0], "pwd"))
		return (TRUE);
	if (ft_is_str_equal(cmds[0], "export") && !cmds[1])
		return (TRUE);
	return (FALSE);
}

t_bool	ft_is_parent(char **cmds)
{
	if (!cmds || !cmds[0])
		return (FALSE);
	if (ft_is_str_equal(cmds[0], "cd"))
		return (TRUE);
	if (ft_is_str_equal(cmds[0], "exit"))
		return (TRUE);
	if (ft_is_str_equal(cmds[0], "unset"))
		return (TRUE);
	if (ft_is_str_equal(cmds[0], "export") && cmds[1])
		return (TRUE);
	return (FALSE);
}

int	ft_route(t_ms *ms, char **cmds)
{
	if (ft_is_str_equal(cmds[0], "cd"))
		return (ft_cd(ms, cmds));
	if (ft_is_str_equal(cmds[0], "echo"))
		return (ft_echo(cmds));
	if (ft_is_str_equal(cmds[0], "env"))
		return (ft_env(ms, cmds));
	if (ft_is_str_equal(cmds[0], "exit"))
		ft_exit(ms, cmds);
	if (ft_is_str_equal(cmds[0], "export"))
		return (ft_export(ms, cmds));
	if (ft_is_str_equal(cmds[0], "pwd"))
		return (ft_pwd(ms));
	if (ft_is_str_equal(cmds[0], "unset"))
		return (ft_unset(ms, cmds));
	return (0);
}
