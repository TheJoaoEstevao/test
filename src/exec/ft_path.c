/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:51 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 17:28:40 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_bool	ft_is_absolute_path(char *path)
{
	if (ft_is_present(path, '/'))
	{
		if (access(path, X_OK) == 0)
			return (TRUE);
	}
	return (FALSE);
}

char	*ft_search_executable(char *cmd, char *path_env)
{
	char	*dir;
	char	*full_path;
	char	*exec_path;

	dir = ft_strtok(path_env, ":");
	while (dir != NULL)
	{
		full_path = ft_strjoin(dir, "/");
		exec_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!access(exec_path, X_OK) && !access(exec_path, F_OK))
			return (exec_path);
		free(exec_path);
		dir = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*ft_find_command_path(char *cmd, t_ms *ms)
{
	char	*path_env;
	char	*exec_path;

	path_env = ft_get_env_value(ms, "PATH");
	if (path_env == NULL)
		return (NULL);
	exec_path = ft_search_executable(cmd, path_env);
	free(path_env);
	return (exec_path);
}

void	ft_handle_null_path(t_ms *ms, char **cmds)
{
	if (ft_is_present(cmds[0], '/'))
	{
		if (access(cmds[0], F_OK))
			ft_cmd_error_exit(ms, cmds[0], 2, NULL);
		else if (access(cmds[0], X_OK))
			ft_cmd_error_exit(ms, cmds[0], 13, NULL);
		else
			ft_cmd_error_exit(ms, cmds[0], 2, NULL);
	}
	else if (cmds[0][0] == '=')
		ft_cmd_error_exit(ms, cmds[0], 127, NULL);
	else if (ft_is_present(cmds[0] + 1, '='))
		ft_cleanup_and_exit(ms, 4);
	else
		ft_cmd_error_exit(ms, cmds[0], 127, NULL);
}
