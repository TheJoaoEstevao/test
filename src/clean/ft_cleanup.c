/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:07 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 15:41:20 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_cleanup_docs_and_sequence(t_ms *ms)
{
	if (ms->doc_list)
	{
		ft_free_token_list(ms->doc_list);
		ms->doc_list = NULL;
	}
	if (ms->buff)
		free(ms->buff);
	if (ms->sequence)
		ft_free_token_list(ms->sequence);
	if (ms->syntax)
		ft_free_cmd_tree(ms->syntax);
}

static void	ft_cleanup_env_and_current(t_ms *ms)
{
	if (ms->locals)
		ft_free_env_list(ms->locals);
	if (ms->current)
		ft_free_str_array(ms->current);
	if (ms->home)
		free(ms->home);
}

static void	ft_cleanup_ui_and_channels(t_ms *ms)
{
	if (ms->track)
		free(ms->track);
	if (ms->display)
		free(ms->display);
	if (ms->channels)
		ft_free_pipe_array(ms);
	if (ms->cache)
		free(ms->cache);
}

void	ft_cleanup_shell(t_ms *ms)
{
	rl_clear_history();
	ft_cleanup_docs_and_sequence(ms);
	ft_cleanup_env_and_current(ms);
	ft_cleanup_ui_and_channels(ms);
	ft_bzero(ms, sizeof(t_ms));
}
