/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:24 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 15:23:18 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static t_bool	ft_is_redirection_token(t_token *token)
{
	return (token->t_type == TOK_RED_IN || token->t_type == TOK_RED_OUT
		|| token->t_type == TOK_APPEND || token->t_type == TOK_HEREDOC);
}

static void	ft_process_redirection_token(t_token **redir_list,
	t_token *current, int *order, t_ms *ms)
{
	t_token	*new_redir;

	new_redir = ft_create_token_node(ft_strdup(current->next->content),
			*order, ms);
	new_redir->t_type = current->t_type;
	ft_add_token_back(redir_list, new_redir);
	(*order)++;
}

static t_token	*ft_parse_redirections(t_token **start, t_token *end, t_ms *ms)
{
	t_token	*redir_list;
	t_token	*current;
	t_token	*to_delete;
	int		order;

	redir_list = NULL;
	order = 0;
	current = *start;
	while (current && current != end)
	{
		if (current->next && ft_is_redirection_token(current))
		{
			ft_process_redirection_token(&redir_list, current, &order, ms);
			to_delete = current;
			current = current->next->next;
			ft_delete_token_pair(start, to_delete->i);
		}
		else
			current = current->next;
	}
	return (redir_list);
}

t_cmd	*ft_create_cmd_node(t_token **start, t_token *end, t_ms *ms)
{
	t_cmd	*cmd_node;

	cmd_node = ft_calloc(1, sizeof(t_cmd));
	cmd_node->mode = CMD_TYPE;
	cmd_node->io = ft_parse_redirections(start, end, ms);
	if (*start != end)
		ft_convt_list_to_array(*start, end, &(cmd_node->cmds));
	return (cmd_node);
}
