/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:37 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:50:38 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_var	*ft_create_env_node(char *name, char *value, int scope)
{
	t_var	*new_node;

	new_node = ft_calloc(1, sizeof(t_var));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->value = value;
	new_node->scope = scope;
	new_node->next = NULL;
	return (new_node);
}

char	*ft_extract_env_name(char *env_str)
{
	char	*name;
	int		len;

	len = 0;
	while (env_str[len])
	{
		if (env_str[len] == '=')
			break ;
		len++;
	}
	name = ft_calloc(1, sizeof(char) * (len + 1));
	if (name)
		return (ft_memcpy(name, env_str, len), name);
	return (NULL);
}

char	*ft_extract_env_value(char *env_str)
{
	char	*value;
	char	*equal_pos;
	int		len;

	equal_pos = ft_strchr(env_str, '=');
	if (equal_pos)
	{
		len = ft_strlen(equal_pos + 1);
		value = ft_calloc(1, sizeof(char) * (len + 1));
		if (value)
			return (ft_memcpy(value, equal_pos + 1, len), value);
	}
	return (NULL);
}

void	ft_init_env_list(t_ms *ms)
{
	int		i;
	char	*name;
	char	*value;
	t_var	*env_node;

	i = 0;
	while (ms->context[i])
	{
		name = ft_extract_env_name(ms->context[i]);
		value = ft_extract_env_value(ms->context[i]);
		if (name && value)
		{
			env_node = ft_create_env_node(name, value, 1);
			ft_append_env_node(&ms->locals, env_node);
		}
		else
		{
			if (name)
				free(name);
			if (value)
				free(value);
		}
		i++;
	}
}
