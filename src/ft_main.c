/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:52:02 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 14:16:32 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	g_signo;

static void	ft_process_input(t_ms *ms)
{
	ms->display = ft_get_prompt(ms);
	ms->buff = readline(ms->display);
	if (!ms->buff)
		ft_handle_exit(ms);
	ft_check_empty_line(ms);
	add_history(ms->buff);
	ms->line_count++;
	ft_space_pipes(ms, ms->buff - 1);
	if (!ft_process_tokens(ms))
		return ;
	ft_check_hdoc(ms->sequence, ms);
	ms->syntax = ft_build_cmd_tree(&(ms->sequence), ms);
	ft_create_pipes(ms);
	ft_executor(ms, ms->syntax, 0);
	ft_close_pipes(ms);
	ft_reset_shell_state(ms);
}

static void	ft_init_shell(t_ms *ms, char **env)
{
	t_var	*oldpwd;
	char	*oldpwd_value;
	char	*home;

	ft_bzero(ms, sizeof(t_ms));
	ms->context = ft_copy_env_array(env);
	ft_init_env_list(ms);
	home = ft_get_env_value(ms, "HOME");
	ms->home = home;
	ms->track = ft_calloc(1, sizeof(t_track));
	ms->out_fd = STDOUT_FILENO;
	ms->exec_num = 1;
	ms->line_count = 1;
	oldpwd_value = ft_get_env_value(ms, "OLDPWD");
	if (!oldpwd_value)
	{
		oldpwd = ft_create_env_node(ft_strdup("OLDPWD"), NULL, 1);
		ft_append_env_node(&ms->locals, oldpwd);
	}
	else
		free(oldpwd_value);
}

void	ft_reset_shell_state(t_ms *ms)
{
	if (ms->buff)
		free(ms->buff);
	if (ms->sequence)
		ft_free_token_list(ms->sequence);
	if (ms->syntax)
		ft_free_cmd_tree(ms->syntax);
	if (ms->display)
		free(ms->display);
	if (ms->channels)
		ft_free_pipe_array(ms);
	if (ms->cache)
		free(ms->cache);
	if (ms->home)
		free(ms->home);
	ft_bzero(ms->track, sizeof(t_track));
	ft_init_shell_vars(ms);
	ms->exec_num = 1;
	ms->in_fd = STDIN_FILENO;
	ms->out_fd = STDOUT_FILENO;
	ft_process_input(ms);
}

int	main(int ac, char **av, char **env)
{
	t_ms	ms;

	ft_close_all_fds();
	if (ac != 1 || av[1])
		return (ft_putstr_fd("minishell cannot receive arguments\n", 2), 2);
	if (!env[0])
		return (ft_putstr_fd("environment is empty\n", 2), 2);
	ft_init_shell(&ms, env);
	ft_setup_signals();
	ft_process_input(&ms);
	rl_clear_history();
	ft_close_all_fds();
	return (0);
}
