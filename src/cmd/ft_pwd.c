/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:31 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 11:31:18 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_pwd(void)
{
	char	*current_path;

	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		ft_putstr_fd("[minishell]: pwd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	ft_putstr_fd(current_path, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(current_path);
	return (0);
}
