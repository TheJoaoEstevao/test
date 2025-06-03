/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:36 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 15:34:43 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_token	*ft_create_token_node(char *word, int i, t_ms *ms)
{
	t_token		*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = word;
	new->t_type = ft_get_token_type(word, ms);
	new->i = i;
	return (new);
}

void	ft_add_token_back(t_token **lexer, t_token *new)
{
	t_token	*last;

	if (!(*lexer))
	{
		(*lexer) = new;
		return ;
	}
	last = (*lexer);
	if (last == new)
		return ;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

t_token	*ft_tokenize_input(char *ui, t_ms *ms)
{
	t_token	*lexer;
	char	*word;

	lexer = NULL;
	while (ui[ms->track->i])
	{
		if (ft_isspace(ui[ms->track->i]))
			ms->track->i++;
		else
		{
			ft_set_word_end(ui, ms);
			word = ft_substr(ui, ms->track->i,
					ms->track->arg_i - ms->track->i);
			ft_add_token_back(&lexer, ft_create_token_node(word,
					ms->track->i, ms));
			ms->track->i = ms->track->arg_i;
		}
	}
	return (lexer);
}
