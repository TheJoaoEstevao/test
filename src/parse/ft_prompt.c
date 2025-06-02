/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:28 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:51:29 by jopedro3         ###   ########.fr       */
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

static char	*ft_get_current_dir(t_ms *ms)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ms->code = 1;
		ft_print_error_four("getcwd error: ", "", "", strerror(errno));
	}
	return (pwd);
}

char	*ft_get_prompt(t_ms *ms)
{
	char	*pwd;
	char	*prompt;
	char	*temp;

	pwd = ft_get_current_dir(ms);
	if (!pwd)
		return (ft_strdup(MS_PREFIX"$ "));
	prompt = ft_strjoin(MS_PREFIX":", pwd);
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
