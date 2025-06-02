/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:17:39 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 16:29:01 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_expand_hdoc_vars(t_ms *sh, char *tmp, char **line)
{
	int		dquote;
	int		squote;

	dquote = 0;
	squote = 0;
	while (*(++tmp))
	{
		if (*tmp == '"' && !squote)
			dquote = !dquote;
		if (*tmp == '\'' && !dquote)
			squote = !squote;
		if (*tmp == '$' && !ft_is_present(SYNTAX_CHARS, *(tmp + 1))
			&& !((dquote || squote) && (*(tmp + 1) == '"'
					|| *(tmp + 1) == '\'')))
		{
			if (ft_expand_dollar(sh, tmp - *line, tmp, line))
			{
				tmp = *line - 1;
				dquote = 0;
				squote = 0;
			}
		}
	}
}
