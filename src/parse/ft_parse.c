/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:21 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 15:55:57 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static int	ft_count_tokens(t_token *start, t_token *end)
{
	int	count;

	count = 0;
	if (!start)
		return (0);
	while (start != end)
	{
		count++;
		start = start->next;
	}
	return (count);
}

void	ft_convt_list_to_array(t_token *start, t_token *end, char ***cmd)
{
	int		i;
	t_token	*current;
	int		len;

	len = ft_count_tokens(start, end);
	*cmd = ft_calloc(len + 1, sizeof(char *));
	if (!*cmd)
		return ;
	current = start;
	i = 0;
	while (current && current != end)
	{
		(*cmd)[i] = ft_strdup(current->content);
		current = current->next;
		i++;
	}
}

static t_cmd	*ft_create_pipe_node(void)
{
	t_cmd	*pipe_node;

	pipe_node = ft_calloc(1, sizeof(t_cmd));
	pipe_node->mode = TOK_PIPE;
	return (pipe_node);
}

static t_token	*ft_find_pipe_token(t_token *start)
{
	while (start && start->kind != TOK_PIPE)
		start = start->next;
	return (start);
}

t_cmd	*ft_build_cmd_tree(t_token **start, t_ms *ms)
{
	t_cmd		*root;
	t_token		*pipe;

	root = NULL;
	if (!*start)
		return (NULL);
	pipe = ft_find_pipe_token(*start);
	if (pipe)
	{
		root = ft_create_pipe_node();
		root->left = ft_create_cmd_node(start, pipe, ms);
		root->right = ft_build_cmd_tree(&(pipe->next), ms);
	}
	else
		root = ft_create_cmd_node(start, NULL, ms);
	return (root);
}
