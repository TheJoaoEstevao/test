/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:10 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 17:58:36 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static int	ft_change_to_home(t_ms *ms)
{
	char	*home_path;

	home_path = ft_get_env_value(ms, "HOME");
	if (!home_path)
	{
		ms->code = 1;
		ft_error_msg("cd: ", "HOME not set", NULL, NULL);
		return (2);
	}
	if (chdir(home_path) == -1)
	{
		ms->code = 1;
		ft_error_msg("cd: ", home_path, ": ", strerror(errno));
		free(home_path);
		return (2);
	}
	else
		ft_update_env_value(ms, "PWD", home_path);
	if (home_path)
		free(home_path);
	return (0);
}

static t_bool	ft_check_home_path(t_ms *ms, char **cmds)
{
	if (cmds && ft_strlen_matrix(cmds) == 1)
	{
		ft_change_to_home(ms);
		return (TRUE);
	}
	return (FALSE);
}

char	*ft_safe_getcwd(t_ms *ms, int error_code)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ms->code = error_code;
		ft_error_msg("getcwd error: ", strerror(errno), NULL, NULL);
	}
	return (pwd);
}

static int	ft_update_pwd(t_ms *ms)
{
	char	*current_path;

	current_path = ft_safe_getcwd(ms, errno);
	if (!current_path)
		return (errno);
	ft_update_env_value(ms, "PWD", current_path);
	free(current_path);
	return (0);
}

int	ft_cd(t_ms *ms, char **cmds)
{
	char	*old_pwd;

	if (ft_check_home_path(ms, cmds))
		return (0);
	if (ft_strlen_matrix(cmds) > 2)
	{
		ms->code = 1;
		ft_error_msg("cd: ", "too many arguments", NULL, NULL);
		return (1);
	}
	else if (cmds[1][0] && chdir(cmds[1]) == -1)
	{
		ft_error_msg("cd: ", cmds[1], ": ", strerror(errno));
		return (1);
	}
	else
	{
		old_pwd = ft_get_env_value(ms, "PWD");
		ft_update_env_value(ms, "OLDPWD", old_pwd);
		free(old_pwd);
		ft_update_pwd(ms);
	}
	return (0);
}
