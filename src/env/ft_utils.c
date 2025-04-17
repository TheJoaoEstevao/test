/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:43 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:50:44 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_free_env_list(t_var *env_list)
{
	t_var	*current;

	while (env_list)
	{
		current = env_list;
		env_list = env_list->next;
		free(current->name);
		current->name = NULL;
		free(current->value);
		current->value = NULL;
		free(current);
		current = NULL;
	}
}

void	ft_free_env_node(t_var *node)
{
	free(node->name);
	node->name = NULL;
	free(node->value);
	node->value = NULL;
	free(node);
	node = NULL;
}

char	**ft_copy_env_array(char **envp)
{
	char	**env_copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env_copy = ft_calloc(1, sizeof(char *) * (i + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (env_copy[i] == NULL)
			return (ft_free_str_array(env_copy), NULL);
		i++;
	}
	return (env_copy);
}

static void	ft_free_list(t_var **list)
{
	t_var	*current;

	while (*list)
	{
		current = *list;
		*list = (*list)->next;
		free(current);
	}
	*list = NULL;
}

void	ft_append_env_node(t_var **head, t_var *new_node)
{
	t_var	*current;

	if (!new_node)
		return (ft_free_list(head));
	if (!*head)
		return (*head = new_node, (void)0);
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}
