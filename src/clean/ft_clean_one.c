/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:49:59 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 10:49:09 by jestevao         ###   ########.fr       */
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

static void	ft_remove_token_pair(t_token **token, t_token *current,
	t_token *prev)
{
	t_token	*temp;

	if (prev)
		prev->next = current->next->next;
	else
	{
		if (!current->prev)
		{
			*token = current->next->next;
			if (*token)
				(*token)->prev = NULL;
		}
		else
		{
			prev = current->prev;
			prev->next = current->next->next;
			*token = current->next->next;
		}
	}
	temp = current->next;
	ft_free_token_node(current);
	ft_free_token_node(temp);
}

void	ft_delete_token_pair(t_token **token, int name)
{
	t_token	*current;
	t_token	*prev;

	current = *token;
	prev = NULL;
	if (!(*token))
		return ;
	while (current && current->next)
	{
		if (current->index == name)
		{
			ft_remove_token_pair(token, current, prev);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
