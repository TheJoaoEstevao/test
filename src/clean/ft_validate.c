/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:43:36 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/17 12:44:04 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_validate_syntax(t_token *lexer)
{
	t_token	*curr;

	curr = lexer;
	if (curr && curr->content[0] == '|')
		return (2);
	while (curr)
	{
		if (curr->content[0] == '|' && ft_is_present(OP_CHARS, \
			curr->content[1]))
			return (2);
		if (curr->content[0] == '<' && ft_is_present("|>", curr->content[1]))
			return (2);
		if (curr->content[0] == '>' && ft_is_present("|<", curr->content[1]))
			return (2);
		if (curr->content[0] == '>' && curr->content[1] == '>' \
			&& ft_is_present(OP_CHARS, curr->content[2]))
			return (2);
		if (curr->content[0] == '<' && curr->content[1] == '<' \
			&& ft_is_present(OP_CHARS, curr->content[2]))
			return (2);
		curr = curr->next;
	}
	if (ft_check_operator_sequence(lexer) || ft_check_empty_redirect(lexer))
		return (2);
	return (0);
}
