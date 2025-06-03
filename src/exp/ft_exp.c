/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:05 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 12:55:09 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static int	ft_handle_pipe_spacing(t_ms *ms, char *str)
{
	if (str != ms->buff && !ft_is_present(DELIMS, *(str - 1)))
		return (ft_expand_cmd_str(" ", str - ms->buff,
				str - ms->buff, &ms->buff));
	if (!ft_is_present(DELIMS, *(str + 1)))
		return (ft_expand_cmd_str(" ", str - ms->buff + 1,
				str - ms->buff + 1, &ms->buff));
	return (0);
}

void	ft_space_pipes(t_ms *ms, char *str)
{
	ms->track->d_quote = 0;
	ms->track->s_quote = 0;
	while (*(++str))
	{
		if (*str == '"' && !ms->track->s_quote)
			ms->track->d_quote = !ms->track->d_quote;
		if (*str == '\'' && !ms->track->d_quote)
			ms->track->s_quote = !ms->track->s_quote;
		if (*str == '|' && !ms->track->d_quote && !ms->track->s_quote)
			if (ft_handle_pipe_spacing(ms, str))
				str = ms->buff - 1;
	}
	ft_bzero(ms->track, sizeof(t_track));
}

static void	ft_remove_quotes(char *str, int *len)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (i < *len)
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
		{
			quote = str[i];
			ft_memmove(str + i, str + i + 1, *len - i);
			(*len)--;
		}
		else if (quote && str[i] == quote)
		{
			quote = 0;
			ft_memmove(str + i, str + i + 1, *len - i);
			(*len)--;
		}
		else
			i++;
	}
}

void	ft_expand_cmds(char ***cmds, t_ms *ms)
{
	ms->track->phrase = -1;
	if (!cmds || !cmds[0] || !cmds[0][0])
		return ;
	ms->matrix = cmds;
	while ((*cmds)[++ms->track->phrase])
	{
		ms->processed = ft_is_present((*cmds)[ms->track->phrase], '$');
		ft_expand_env_vars(ms, (*cmds)[ms->track->phrase] - 1,
			&(*cmds)[ms->track->phrase]);
		if (ms->track->phrase == -1)
			return ;
		ms->len = ft_strlen((*cmds)[ms->track->phrase]);
		ft_remove_quotes((*cmds)[ms->track->phrase], &ms->len);
		if (!(*cmds)[ms->track->phrase][0] && ms->processed)
		{
			free((*cmds)[ms->track->phrase]);
			(*cmds)[ms->track->phrase] = NULL;
		}
	}
	if (ft_remove_null_entries(*cmds, ms->track->phrase) == ms->track->phrase)
	{
		free(*cmds);
		*cmds = NULL;
	}
}

char	*ft_trim_spaces(char *str)
{
	int	i;
	int	j;
	int	space_flag;

	i = 0;
	j = 0;
	space_flag = 1;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (ft_isspace(str[i]) && space_flag)
		{
			str[j++] = ' ';
			space_flag = 0;
		}
		else if (!ft_isspace(str[i]))
		{
			str[j++] = str[i];
			space_flag = 1;
		}
		i++;
	}
	str[j - (j > 0 && ft_isspace(str[j - 1]))] = 0;
	return (str);
}
