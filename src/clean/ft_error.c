/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:07 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 15:22:27 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_bool	ft_check_operator_sequence(t_token *token)
{
	t_token	*curr;
	t_token	*previous;

	curr = token;
	while (curr)
	{
		previous = curr;
		curr = curr->next;
		if (curr && previous->t_type && curr->t_type)
		{
			if (previous->t_type == TOK_PIPE && curr->t_type != TOK_PIPE)
				continue ;
			else
				return (TRUE);
		}
	}
	return (FALSE);
}

void	ft_error_msg(char *s1, char *s2, char *s3, char *s4)
{
	ft_putstr_fd("[minishell]: ", 2);
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	if (s3)
		ft_putstr_fd(s3, 2);
	if (s4)
		ft_putstr_fd(s4, 2);
	ft_putchar_fd('\n', 2);
}

t_bool	ft_check_empty_redirect(t_token *token)
{
	t_token	*curr;
	t_token	*previous;

	curr = token;
	while (curr)
	{
		previous = curr;
		curr = curr->next;
		if (!curr && previous->t_type)
			return (TRUE);
	}
	return (FALSE);
}

void	ft_syntax_error(char *token, t_ms *ms)
{
	if (token)
		ft_error_msg("syntax error near unexpected token `", token, "'", NULL);
	else
		ft_error_msg("syntax error near unexpected token `",
			"newline", "'", NULL);
	ms->code = 2;
}
