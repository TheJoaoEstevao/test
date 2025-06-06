/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:00 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 15:38:13 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_expand_dollar(t_ms *ms, int pos, char *input, char **arg_i)
{
	char	*name;
	char	*env_val;

	if (g_signo == 130)
		ms->code = 130;
	if (!input[1])
		return (0);
	if (input[1] == '?')
		return (ft_expand_and_free(ft_itoa(ms->code), pos, pos + 2, arg_i));
	ms->len = 1;
	while (ft_isalpha(input[ms->len]) || input[ms->len] == '_')
		ms->len++;
	ms->len += (ft_isalnum(input[ms->len]) > 0);
	while (ms->len > 2 && (ft_isalnum(input[ms->len]) || input[ms->len] == '_'))
		ms->len++;
	name = ft_substr(input, 1, ms->len - 1);
	env_val = ft_get_env_value(ms, name);
	if (env_val)
		ft_handle_valid_env(pos, ms, env_val, arg_i);
	else
		ft_expand_cmd_str("", pos, pos + ms->len, arg_i);
	free(name);
	return (1);
}

int	ft_check_quote_pairs(const char *str, t_ms *ms)
{
	int		quote_count;
	char	quote_char;

	quote_count = 0;
	while (*str && (quote_count % 2 == 0 || quote_count == 0))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote_char = *str++;
			quote_count++;
			while (*str && *str != quote_char)
				str++;
			if (*str && *str == quote_char)
				quote_count++;
		}
		if (*str)
			str++;
	}
	if (quote_count % 2 != 0)
	{
		ft_putstr_fd("[minishell]: Open quote is found.\n", 2);
		ft_reset_shell_state(ms);
	}
	return (quote_count);
}

void	ft_expand_env_vars(t_ms *ms, char *input, char **arg_i)
{
	ms->track->d_quote = 0;
	ms->track->s_quote = 0;
	while (*(++input))
	{
		if (*input == '"' && !ms->track->s_quote)
			ms->track->d_quote = !ms->track->d_quote;
		if (*input == '\'' && !ms->track->d_quote)
			ms->track->s_quote = !ms->track->s_quote;
		if (*input == '$' && !ft_is_present(SYNTAX_CHARS, *(input + 1))
			&& !ms->track->s_quote && !((ms->track->d_quote
					|| ms->track->s_quote) && (*(input + 1) == '"'
					|| *(input + 1) == '\'')))
		{
			if (ft_expand_dollar(ms, input - *arg_i, input, arg_i))
			{
				if (ms->track->arg_i == -1)
					return ;
				input = *arg_i - 1;
				ms->track->d_quote = 0;
				ms->track->s_quote = 0;
			}
		}
	}
	ft_check_quote_pairs(*arg_i, ms);
}

void	ft_update_cmd_array(t_ms *ms, char *value, char **arg_i)
{
	int		idx;
	char	**words;

	idx = -1;
	free(*arg_i);
	words = ft_split(value, ' ');
	free(*ms->matrix);
	*ms->matrix = ft_calloc(ft_count_words(value, ' ') + 1, sizeof(char *));
	while (words[++idx])
		(*ms->matrix)[idx] = ft_strdup(words[idx]);
	ft_free_str_array(words);
	ms->track->arg_i = -1;
}
