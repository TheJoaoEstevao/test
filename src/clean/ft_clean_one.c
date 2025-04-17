/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:49:59 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:50:00 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_free_token_node(t_token *node)
{
	if (node)
	{
		if (node->content)
			free(node->content);
		node->prev = NULL;
		free(node);
	}
}

static void	ft_remove_token_pair(t_token **lexer, t_token *current, \
t_token *prev)
{
	t_token	*temp;

	if (prev)
		prev->next = current->next->next;
	else
	{
		if (!current->prev)
		{
			*lexer = current->next->next;
			if (*lexer)
				(*lexer)->prev = NULL;
		}
		else
		{
			prev = current->prev;
			prev->next = current->next->next;
			*lexer = current->next->next;
		}
	}
	temp = current->next;
	ft_free_token_node(current);
	ft_free_token_node(temp);
}

void	ft_delete_token_pair(t_token **lexer, int key)
{
	t_token	*current;
	t_token	*prev;

	current = *lexer;
	prev = NULL;
	if (!(*lexer))
		return ;
	while (current && current->next)
	{
		if (current->index == key)
		{
			ft_remove_token_pair(lexer, current, prev);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
