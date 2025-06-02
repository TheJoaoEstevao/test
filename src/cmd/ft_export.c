/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:22 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 12:46:35 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_update_env_var(t_ms *ms, char *key, char *value, int scope)
{
	t_var	*env_node;

	env_node = NULL;
	if (scope == 1 && ft_strcmp(key, "_")
		&& !ft_update_env_value(ms, key, value))
	{
		env_node = ft_create_env_node(key, value, 1);
		ft_append_env_node(&ms->locals, env_node);
	}
	else if (!value && scope == 0 && ft_strcmp(key, "_"))
	{
		env_node = ft_create_env_node(key, value, 0);
		ft_append_env_node(&ms->locals, env_node);
	}
	else
	{
		free(key);
		free(value);
	}
}

static int	ft_validate_key_chars(char *key, char *equals_pos)
{
	int	index;

	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		if (equals_pos)
			free(key);
		return (1);
	}
	index = 1;
	while (key[index])
	{
		if (!ft_isalnum(key[index]) && key[index] != '_')
		{
			if (equals_pos)
				free(key);
			return (1);
		}
		index++;
	}
	if (equals_pos)
		free(key);
	return (0);
}

int	ft_validate_key(t_ms *ms, char *str)
{
	char	*equals_pos;
	char	*key;

	if (!str || ft_strlen(str) == 0)
		return (1);
	(void)ms;
	equals_pos = ft_strchr(str, '=');
	if (equals_pos)
	{
		key = ft_substr(str, 0, equals_pos - str);
		if (!key)
			return (1);
	}
	else
		key = str;
	return (ft_validate_key_chars(key, equals_pos));
}

int	ft_process_export(t_ms *ms, char *cmd)
{
	char	*key;
	char	*value;

	if (ft_validate_key(ms, cmd) == 0)
	{
		key = ft_extract_env_name(cmd);
		value = ft_extract_env_value(cmd);
		if (ft_strchr(cmd, '='))
			ft_update_env_var(ms, key, value, 1);
		else
			ft_update_env_var(ms, key, value, 0);
		return (0);
	}
	return (1);
}

int	ft_export(t_ms *ms, char **cmds)
{
	int	index;
	int	has_error;

	index = 1;
	has_error = 0;
	if (ft_strlen_matrix(cmds) == 1)
	{
		ft_export_print(ms);
		return (0);
	}
	while (cmds[index])
	{
		if (ft_validate_key(ms, cmds[index]))
		{
			ft_print_error_four("export: '", cmds[index],
				"': ", "not a valid identifier");
			has_error = 1;
		}
		else
			ft_process_export(ms, cmds[index]);
		index++;
	}
	ft_update_env_array(ms);
	return (has_error);
}
