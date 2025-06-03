/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:33 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 12:51:59 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_delete_env_var(t_ms *ms, char *name)
{
	t_var	*target;
	t_var	*prev;
	t_var	*current;

	prev = NULL;
	current = ms->locals;
	while (current)
	{
		if (ft_is_str_equal(current->name, name))
		{
			target = current;
			if (prev)
				prev->next = current->next;
			else
				ms->locals = current->next;
			ft_free_env_node(target);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_ms *ms, char **cmds)
{
	int	index;

	index = 1;
	if (ft_strlen_matrix(cmds) == 1)
		return (0);
	else
	{
		while (cmds[index])
			ft_delete_env_var(ms, cmds[index++]);
		ft_update_env_array(ms);
	}
	return (0);
}
