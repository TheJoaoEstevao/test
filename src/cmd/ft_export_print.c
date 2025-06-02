/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:20 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 17:17:52 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_swap_env_vars(t_var *a, t_var *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

void	ft_sort_env_list(t_var *env_list)
{
	int		swapped;
	t_var	*current;

	if (!env_list || !env_list->next)
		return ;
	while (1)
	{
		swapped = 0;
		current = env_list;
		while (current->next)
		{
			if (ft_strncmp(current->name, current->next->name,
					ft_strlen(current->name)
					+ ft_strlen(current->next->name)) > 0)
			{
				ft_swap_env_vars(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		if (!swapped)
			break ;
	}
}

void	ft_export_print(t_ms *ms)
{
	t_var	*current;

	current = ms->locals;
	ft_sort_env_list(current);
	while (current)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(current->name, 1);
		if (current->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
}
