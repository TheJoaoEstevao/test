/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:28 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 10:38:52 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_handle_exit(t_ms *ms)
{
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	ft_cleanup_shell(ms);
	exit(ms->code);
}

void	ft_check_empty_line(t_ms *ms)
{
	char	*trimmed;

	trimmed = NULL;
	trimmed = ft_strtrim(ms->buff, DELIMS);
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		ft_reset_shell_state(ms);
	}
	free(trimmed);
}

char	*ft_get_prompt(t_ms *ms)
{
	char	*pwd;
	char	*prompt;
	char	*temp;

	pwd = ft_safe_getcwd(ms, 1);
	if (!pwd)
		return (ft_strdup("[minishell]$ "));
	prompt = ft_strjoin("[minishell]:", pwd);
	temp = ft_strjoin(prompt, "$ ");
	free(prompt);
	prompt = temp;
	free(pwd);
	return (prompt);
}

void	ft_init_shell_vars(t_ms *ms)
{
	ms->buff = NULL;
	ms->sequence = NULL;
	ms->syntax = NULL;
	ms->display = NULL;
	ms->channels = NULL;
	ms->cache = NULL;
	ms->matrix = NULL;
	ms->home = NULL;
}
