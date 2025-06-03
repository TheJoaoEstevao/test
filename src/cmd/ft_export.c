/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:22 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 13:16:37 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_update_env_var(t_ms *ms, char *name, char *value, int scope)
{
	t_var	*env_node;

	env_node = NULL;
	if (scope == 1 && !ft_update_env_value(ms, name, value))
	{
		env_node = ft_create_env_node(name, value, 1);
		ft_append_env_node(&ms->locals, env_node);
	}
	else if (scope == 0 && !ft_update_env_value(ms, name, value))
	{
		env_node = ft_create_env_node(name, value, 0);
		ft_append_env_node(&ms->locals, env_node);
	}
	else
	{
		free(name);
		free(value);
	}
}

static int	ft_validate_name_chars(char *name, char *equals_pos)
{
	int	index;

	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		if (equals_pos)
			free(name);
		return (1);
	}
	index = 1;
	while (name[index])
	{
		if (!ft_isalnum(name[index]) && name[index] != '_')
		{
			if (equals_pos)
				free(name);
			return (1);
		}
		index++;
	}
	if (equals_pos)
		free(name);
	return (0);
}

int	ft_validate_name(char *str)
{
	int		equals_pos;
	char	*name;

	if (!str || ft_strlen(str) == 0)
		return (1);
	if (ft_is_present(str, '='))
	{
		equals_pos = 0;
		while (str[equals_pos] && str[equals_pos] != '=')
			equals_pos++;
		name = ft_substr(str, 0, equals_pos);
		if (!name)
			return (1);
		return (ft_validate_name_chars(name, name));
	}
	else
		return (ft_validate_name_chars(str, NULL));
}

int	ft_process_export(t_ms *ms, char *cmd)
{
	char	*name;
	char	*value;

	if (ft_validate_name(cmd) == 0)
	{
		name = ft_extract_env_name(cmd);
		value = ft_extract_env_value(cmd);
		if (ft_is_present(cmd, '='))
			ft_update_env_var(ms, name, value, 1);
		else
			ft_update_env_var(ms, name, value, 0);
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
		if (ft_validate_name(cmds[index]))
		{
			ft_error_msg("export: '",
				cmds[index], "': not a valid identifier", NULL);
			has_error = 1;
		}
		else
			ft_process_export(ms, cmds[index]);
		index++;
	}
	ft_update_env_array(ms);
	return (has_error);
}
