/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:25 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:50:26 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_bool	ft_compare_strings(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;

	if (!str1 || !str2)
		return (FALSE);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 != len2)
		return (FALSE);
	return (!ft_strncmp(str1, str2, len1));
}

t_bool	ft_is_child(char **cmds)
{
	if (!cmds || !cmds[0])
		return (FALSE);
	if (ft_compare_strings(cmds[0], "echo"))
		return (TRUE);
	if (ft_compare_strings(cmds[0], "env"))
		return (TRUE);
	if (ft_compare_strings(cmds[0], "pwd"))
		return (TRUE);
	if (ft_compare_strings(cmds[0], "export") && !cmds[1])
		return (TRUE);
	return (FALSE);
}

t_bool	ft_is_parent(char **cmds)
{
	if (!cmds || !cmds[0])
		return (FALSE);
	if (ft_compare_strings(cmds[0], "cd"))
		return (TRUE);
	if (ft_compare_strings(cmds[0], "exit"))
		return (TRUE);
	if (ft_compare_strings(cmds[0], "unset"))
		return (TRUE);
	if (ft_compare_strings(cmds[0], "export") && cmds[1])
		return (TRUE);
	return (FALSE);
}

int	ft_route(t_ms *ms, char **cmds)
{
	if (ft_compare_strings(cmds[0], "cd"))
		return (ft_cd(ms, cmds));
	if (ft_compare_strings(cmds[0], "echo"))
		return (ft_echo(cmds));
	if (ft_compare_strings(cmds[0], "env"))
		return (ft_env(ms, cmds));
	if (ft_compare_strings(cmds[0], "exit"))
		ft_exit(ms, cmds);
	if (ft_compare_strings(cmds[0], "export"))
		return (ft_export(ms, cmds));
	if (ft_compare_strings(cmds[0], "pwd"))
		return (ft_pwd(ms));
	if (ft_compare_strings(cmds[0], "unset"))
		return (ft_unset(ms, cmds));
	return (0);
}
