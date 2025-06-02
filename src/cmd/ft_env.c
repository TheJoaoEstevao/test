/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:15 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 12:47:14 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_print_env_list(t_ms *ms)
{
	t_var	*current;
	char	*env_entry;

	current = ms->locals;
	while (current)
	{
		if (current->scope && current->value)
		{
			env_entry = ft_strjoin(current->name, "=");
			ft_putstr_fd(env_entry, STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			free(env_entry);
		}
		current = current->next;
	}
}

int	ft_env(t_ms *ms, char **cmds)
{
	if (ft_strlen_matrix(cmds) > 1)
	{
		ms->code = 127;
		return (ft_print_error_three(ms, "env: '",
				cmds[1], "': No such" "file or directory"));
	}
	else
		ft_print_env_list(ms);
	return (0);
}
