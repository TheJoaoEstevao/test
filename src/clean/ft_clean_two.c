/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:04 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 10:35:14 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_free_token_list(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	next = NULL;
	if (!head)
		return ;
	while (current)
	{
		next = current->next;
		if (current->content)
		{
			free(current->content);
			current->content = NULL;
		}
		free(current);
		current = next;
	}
}

void	ft_free_str_array(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	ft_free_pipe_array(t_ms *ms)
{
	int	i;

	i = -1;
	if (ms == NULL || ms->channels == NULL)
		return ;
	while (++i < ms->exec_num)
		free(ms->channels[i]);
	free(ms->channels);
}
