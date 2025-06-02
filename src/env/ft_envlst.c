/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:40 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 16:54:09 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static int	ft_env_list_size(t_var *list)
{
	int	count;

	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}

static void	ft_join_env_entry(t_var *env_var, char **env_array, int index)
{
	char	*temp;

	if (env_var->scope)
	{
		temp = ft_nl_strjoin(env_array[index], env_var->name);
		free(env_array[index]);
		env_array[index] = temp;
		if (env_var->value)
		{
			temp = ft_nl_strjoin(env_array[index], "=");
			free(env_array[index]);
			env_array[index] = temp;
			temp = ft_nl_strjoin(env_array[index], env_var->value);
			free(env_array[index]);
			env_array[index] = temp;
		}
	}
}

void	ft_update_env_array(t_ms *ms)
{
	t_var	*original;
	int		array_size;
	int		index;

	array_size = ft_env_list_size(ms->locals);
	if (ms->context)
		ft_free_str_array(ms->context);
	if (!ms->locals)
	{
		ms->context = NULL;
		return ;
	}
	ms->context = ft_calloc(1, sizeof(char *) * (array_size + 1));
	original = ms->locals;
	index = 0;
	ms->context[index] = NULL;
	while (ms->locals)
	{
		ft_join_env_entry(ms->locals, ms->context, index);
		index++;
		ms->locals = ms->locals->next;
	}
	ms->locals = original;
}

char	*ft_get_env_value(t_ms *ms, char *name)
{
	t_var	*original;
	char	*value;

	original = ms->locals;
	value = NULL;
	while (ms->locals)
	{
		if (ft_is_str_equal(name, ms->locals->name) && ms->locals->scope)
		{
			if (ms->locals->value)
				value = ft_strdup(ms->locals->value);
			else
				value = ft_strdup("");
			break ;
		}
		ms->locals = ms->locals->next;
	}
	ms->locals = original;
	return (value);
}

int	ft_update_env_value(t_ms *ms, char *name, char *new_value)
{
	t_var	*original;

	original = ms->locals;
	while (ms->locals)
	{
		if (ft_is_str_equal(name, ms->locals->name))
		{
			free(ms->locals->value);
			ms->locals->value = ft_strdup(new_value);
			ms->locals->scope = 1;
			ms->locals = original;
			ft_update_env_array(ms);
			return (1);
		}
		ms->locals = ms->locals->next;
	}
	ms->locals = original;
	return (0);
}
