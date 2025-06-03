/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:17 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 11:22:20 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static t_bool	ft_check_longlong(char *str)
{
	int	is_negative;
	int	length;

	is_negative = 0;
	if (*str == '-')
	{
		is_negative = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str == '0')
		str++;
	length = ft_strlen(str);
	if (length > 19)
		return (FALSE);
	if (is_negative)
		return (ft_strncmp(str, MIN_LLONG_STR, length) <= 0);
	else
		return (ft_strncmp(str, MAX_LLONG_STR, length) <= 0);
}

static t_bool	ft_is_exit_num(char *cmd)
{
	int	index;

	index = 0;
	if ((cmd[index] == '-' || cmd[index] == '+') && !cmd[index + 1])
		return (FALSE);
	if ((cmd[index] == '-' || cmd[index] == '+') && cmd[index + 1])
		index++;
	while (cmd[index])
	{
		if (!ft_isdigit(cmd[index]))
			return (FALSE);
		index++;
	}
	return (TRUE);
}

static long long	ft_normalize_exit_code(char *str)
{
	long long	exit_code;

	exit_code = (long long)ft_atol(str);
	if (exit_code >= 0)
		exit_code = exit_code % 256;
	else
		exit_code = 256 + (exit_code % 256);
	return (exit_code);
}

void	ft_exit(t_ms *ms, char **cmds)
{
	unsigned long long	exit_code;

	printf("exit\n");
	exit_code = 0;
	if (!ft_strlen_matrix(cmds))
		exit_code = 0;
	else if (cmds[1] && (!ft_is_exit_num(cmds[1])
			|| !ft_check_longlong(cmds[1])))
	{
		exit_code = 2;
		ft_error_msg("exit: ", cmds[1], ": numeric argument required", NULL);
	}
	else if (ft_strlen_matrix(cmds) > 2)
	{
		ms->code = 1;
		ft_error_msg("exit: too many arguments", NULL, NULL, NULL);
		ft_reset_shell_state(ms);
	}
	else
		exit_code = ft_normalize_exit_code(cmds[1]);
	ft_cleanup_shell(ms);
	exit(exit_code);
}
