/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:07 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 15:38:42 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_remove_null_entries(char **cmds, int count)
{
	int	read_pos;
	int	write_pos;
	int	null_count;

	null_count = count;
	read_pos = 0;
	write_pos = 0;
	while (read_pos < count)
	{
		if (cmds[read_pos] != NULL)
		{
			cmds[write_pos++] = cmds[read_pos];
			null_count--;
		}
		read_pos++;
	}
	cmds[write_pos] = NULL;
	return (null_count);
}

int	ft_expand_cmd_str(char *value, int start, int end, char **arg_i)
{
	char	*prefix;
	char	*suffix;
	char	*temp;

	prefix = ft_substr(*arg_i, 0, start);
	suffix = ft_substr(*arg_i, end, ft_strlen(*arg_i) - end + 1);
	free(*arg_i);
	*arg_i = ft_nl_strjoin(prefix, value);
	if (!*arg_i)
	{
		free(prefix);
		free(suffix);
		return (0);
	}
	temp = *arg_i;
	*arg_i = ft_nl_strjoin(*arg_i, suffix);
	if (!*arg_i)
		*arg_i = temp;
	else
		free(temp);
	free(prefix);
	free(suffix);
	return (1);
}

void	ft_handle_valid_env(int pos, t_ms *ms, char *env_val, char **arg_i)
{
	char	*tmp;
	char	*trimmed;

	tmp = ft_substr(*arg_i, pos + ms->len,
			ft_strlen(*arg_i) - pos + ms->len + 1);
	if (ms->track->d_quote)
		ft_expand_cmd_str(env_val, pos, pos + ms->len, arg_i);
	else if (ft_count_words(env_val, ' ') > 1 && !pos && !tmp[0]
		&& ft_strlen_matrix(*ms->matrix) == 1)
	{
		trimmed = ft_strdup(env_val);
		ft_update_cmd_array(ms, ft_trim_spaces(trimmed), arg_i);
		free(trimmed);
	}
	else
	{
		trimmed = ft_strdup(env_val);
		ft_expand_cmd_str(ft_trim_spaces(trimmed), pos,
			pos + ms->len, arg_i);
		free(trimmed);
	}
	free(tmp);
	free(env_val);
}

int	ft_expand_and_free(char *name, int start, int end, char **arg_i)
{
	ft_expand_cmd_str(name, start, end, arg_i);
	free(name);
	return (1);
}
