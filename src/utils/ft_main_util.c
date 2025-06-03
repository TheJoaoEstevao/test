/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:49 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 13:50:55 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static t_bool	ft_check_token_sequence(t_token *curr, t_ms *ms)
{
	if (curr->content[0] == '>' && curr->next
		&& curr->next->content[0] == '>'
		&& curr->next->content[1] == '>')
		return (ft_syntax_error(">>", ms), FALSE);
	if (curr->content[0] == '<' && curr->next
		&& curr->next->content[0] == '|')
		return (ft_syntax_error("|", ms), FALSE);
	if (curr->content[0] == '|' && curr->next
		&& curr->next->content[0] == '>')
	{
		if (!curr->next->next || !curr->next->next->content)
			return (ft_syntax_error("newline", ms), FALSE);
	}
	return (TRUE);
}

static int	ft_validate_syntax(t_token *lexer)
{
	t_token	*curr;

	curr = lexer;
	if (curr && curr->content[0] == '|')
		return (2);
	while (curr)
	{
		if (curr->content[0] == '|' && ft_is_present(OP_CHARS,
				curr->content[1]))
			return (2);
		if (curr->content[0] == '<' && ft_is_present("|>", curr->content[1]))
			return (2);
		if (curr->content[0] == '>' && ft_is_present("|<", curr->content[1]))
			return (2);
		if (curr->content[0] == '>' && curr->content[1] == '>'
			&& ft_is_present(OP_CHARS, curr->content[2]))
			return (2);
		if (curr->content[0] == '<' && curr->content[1] == '<'
			&& ft_is_present(OP_CHARS, curr->content[2]))
			return (2);
		curr = curr->next;
	}
	if (ft_check_operator_sequence(lexer) || ft_check_empty_redirect(lexer))
		return (2);
	return (0);
}

static t_bool	ft_validate_final_syntax(t_token *curr, t_ms *ms)
{
	if (ft_validate_syntax(ms->sequence))
	{
		if (curr && curr->content[0] == '|')
			ft_syntax_error("|", ms);
		else
			ft_syntax_error("newline", ms);
		ms->code = 2;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	ft_process_tokens(t_ms *ms)
{
	t_token	*curr;

	ms->sequence = ft_tokenize_input(ms->buff, ms);
	if (!ms->sequence)
		return (ft_reset_shell_state(ms), FALSE);
	curr = ms->sequence;
	if (curr && curr->content[0] == '|')
	{
		ft_syntax_error("|", ms);
		ms->code = 2;
		return (ft_reset_shell_state(ms), FALSE);
	}
	while (curr && curr->next)
	{
		if (!ft_check_token_sequence(curr, ms))
			return (ft_reset_shell_state(ms), FALSE);
		curr = curr->next;
	}
	if (!ft_validate_final_syntax(curr, ms))
		return (ft_reset_shell_state(ms), FALSE);
	return (TRUE);
}
