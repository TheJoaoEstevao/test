/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:39 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:51:40 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_bool	ft_is_present(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (TRUE);
		str++;
	}
	return (FALSE);
}

int	ft_get_token_type(char *word, t_ms *ms)
{
	if (word[0] == '|' && !ft_is_present(OP_CHARS, word[1]))
	{
		ms->exec_num++;
		return (TOK_PIPE);
	}
	if (word[0] == '>' && word[1] == '>' && !ft_is_present(OP_CHARS, word[2]))
		return (TOK_APPEND);
	if (word[0] == '<' && word[1] == '<' && !ft_is_present(OP_CHARS, word[2]))
	{
		ms->doc_num++;
		return (TOK_HEREDOC);
	}
	if (word[0] == '<' && !ft_is_present(OP_CHARS, word[1]))
		return (TOK_RED_IN);
	if (word[0] == '>' && !ft_is_present(OP_CHARS, word[1]))
		return (TOK_RED_OUT);
	return (TOK_WORD);
}

static void	ft_advance_quote(char *str, int *j, char next_char)
{
	(*j)++;
	while (str[*j] && str[*j] != next_char)
		(*j)++;
	if (str[*j] == next_char)
		(*j)++;
}

static void	ft_advance_word(char *str, int *j)
{
	t_bool	quotes;

	if (str[*j] && ft_is_present(OP_CHARS, str[*j]))
	{
		while (str[*j] && ft_is_present(OP_CHARS, str[*j]))
			(*j)++;
		return ;
	}
	while (str[*j] && !ft_is_present(DELIMS, str[*j]) && \
	!ft_is_present(OP_CHARS, str[*j]))
	{
		if (ft_is_present("\"\'", str[*j]))
		{
			quotes = !quotes;
			ft_advance_quote(str, j, str[*j]);
		}
		else
			(*j)++;
	}
}

void	ft_set_word_end(char *ui, t_ms *ms)
{
	ms->track->phrase = ms->track->cursor;
	if (ui[ms->track->phrase] == '\"' || ui[ms->track->phrase] == '\'')
	{
		ft_advance_quote(ui, &ms->track->phrase, ui[ms->track->phrase]);
		while (!ft_isspace(ui[ms->track->phrase]) && \
		ui[ms->track->phrase] != '\0')
		{
			if (ui[ms->track->phrase] == '\"' || \
			ui[ms->track->phrase] == '\'')
				ft_advance_quote(ui, &ms->track->phrase, \
				ui[ms->track->phrase]);
			else
				ft_advance_word(ui, &ms->track->phrase);
		}
	}
	else
		ft_advance_word(ui, &ms->track->phrase);
}
