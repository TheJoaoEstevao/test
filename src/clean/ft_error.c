/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:07 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:50:08 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_bool	ft_check_operator_sequence(t_token *lexer)
{
	t_token	*curr;
	t_token	*previous;

	curr = lexer;
	while (curr)
	{
		previous = curr;
		curr = curr->next;
		if (curr && previous->kind && curr->kind)
		{
			if (previous->kind == TOK_PIPE && curr->kind != TOK_PIPE)
				continue ;
			else
				return (TRUE);
		}
	}
	return (FALSE);
}

int	ft_print_error_three(t_ms *sh, char *str1, char *str2, char *str3)
{
	ft_putstr_fd("[minishell]: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	ft_putstr_fd("\n", 2);
	return (sh->code);
}

void	ft_print_error_four(char *str1, char *str2, char *str3, char *str4)
{
	ft_putstr_fd("[minishell]: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	ft_putstr_fd(str4, 2);
	ft_putstr_fd("\n", 2);
}

t_bool	ft_check_empty_redirect(t_token *lexer)
{
	t_token	*curr;
	t_token	*previous;

	curr = lexer;
	while (curr)
	{
		previous = curr;
		curr = curr->next;
		if (!curr && previous->kind)
			return (TRUE);
	}
	return (FALSE);
}

void	ft_syntax_error(char *token, t_ms *ms)
{
	static t_bool	error_printed = FALSE;

	if (!error_printed)
	{
		ft_putstr_fd("[minishell]: syntax error near unexpected token `", 2);
		if (token)
			ft_putstr_fd(token, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
		error_printed = TRUE;
	}
	ms->code = 2;
}
