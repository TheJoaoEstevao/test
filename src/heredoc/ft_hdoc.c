/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:10 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:51:11 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_token	*ft_heredoc_new(char *limiter)
{
	t_token	*hdoc_node;

	hdoc_node = ft_calloc(1, sizeof(t_token));
	hdoc_node->limit = limiter;
	hdoc_node->kind = TOK_HEREDOC;
	return (hdoc_node);
}

void	ft_rm_quotes_hdoc(char *str)
{
	char	quote;
	int		i;
	int		len;

	quote = 0;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
		{
			quote = str[i];
			ft_memmove(str + i, str + i + 1, len - i);
			len--;
		}
		else if (quote && str[i] == quote)
		{
			quote = 0;
			ft_memmove(str + i, str + i + 1, len - i);
			len--;
		}
		else
			i++;
	}
}

static void	ft_init_and_up_cache(t_token *current, t_ms *ms)
{
	char	*old_cache;

	if (current->kind == TOK_HEREDOC)
	{
		ms->doc_state = 0;
		old_cache = ms->cache;
		ms->cache = ft_nl_strjoin(ms->cache, "a");
		free(old_cache);
		ft_check_quote_pairs(current->next->content, ms);
		if (ft_strchr(current->next->content, '"') || \
			ft_strchr(current->next->content, '\''))
			ms->doc_state = 1;
	}
}

void	ft_check_hdoc(t_token *lexer, t_ms *ms)
{
	t_token	*current;
	t_token	*new_doc;

	current = lexer;
	ms->cache = ft_calloc(2, sizeof(char));
	ms->cache[0] = '.';
	while (current && current->next)
	{
		if (current->kind == TOK_HEREDOC)
		{
			ft_init_and_up_cache(current, ms);
			ft_rm_quotes_hdoc(current->next->content);
			new_doc = ft_heredoc_new(current->next->content);
			new_doc->content = ft_strdup(ms->cache);
			ft_add_token_back(&ms->doc_list, new_doc);
			ft_create_heredoc(new_doc, ms);
		}
		current = current->next;
	}
}

void	ft_process_redirect_heredoc(t_ms *ms, t_token **in_redirs)
{
	t_token	*current;

	current = ms->doc_list;
	ms->doc_list = ms->doc_list->next;
	current->next = NULL;
	ft_add_token_back(in_redirs, current);
}
