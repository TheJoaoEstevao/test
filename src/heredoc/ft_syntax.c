/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:17:39 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/17 13:17:41 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_print_syntax_error(char *token)
{
	ft_putstr_fd("[minishell]: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

int	ft_check_pipe_syntax(t_ms *ms, char *str)
{
	char	*trimmed;

	if (!str)
		return (0);
	trimmed = ft_strtrim(str, DELIMS);
	if (trimmed[0] == '|')
	{
		ft_syntax_error("|", ms);
		free(trimmed);
		return (2);
	}
	if (trimmed[0] == '>' || trimmed[0] == '<')
	{
		if (!trimmed[1] || (trimmed[1] == trimmed[0] && !trimmed[2]))
			ft_syntax_error("newline", ms);
		else if (trimmed[0] == '>' && trimmed[1] == '>' && trimmed[2] == '>')
			ft_syntax_error(">", ms);
		else
			ft_syntax_error(trimmed, ms);
		free(trimmed);
		return (2);
	}
	free(trimmed);
	return (0);
}

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
		if (*tmp == '$' && !ft_strchr(SYNTAX_CHARS, *(tmp + 1)) && \
		!((dquote || squote) && (*(tmp + 1) == '"' || *(tmp + 1) == '\'')))
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
