/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:02 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 10:35:01 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_cleanup_heredoc(t_ms *ms)
{
	char	*filename;
	char	*temp;
	int		index;

	index = 0;
	filename = ft_calloc(2, sizeof(char));
	filename[0] = '.';
	temp = ft_strjoin(filename, "a");
	free(filename);
	filename = temp;
	while (!access(filename, R_OK) && index++ < ms->doc_num)
	{
		unlink(filename);
		temp = ft_strjoin(filename, "a");
		free(filename);
		filename = temp;
	}
	free(filename);
}

void	ft_free_cmd_tree(t_cmd *root)
{
	if (!root)
		return ;
	if (root->cmds && root->cmds[0])
		ft_free_str_array(root->cmds);
	root->cmds = NULL;
	if (root->io)
		ft_free_token_list(root->io);
	root->io = NULL;
	ft_free_cmd_tree(root->left);
	ft_free_cmd_tree(root->right);
	free(root);
}

void	ft_cleanup_and_exit(t_ms *ms, int exit_code)
{
	if (ms->in_fd > 2)
		ft_close(ms->in_fd);
	if (ms->out_fd > 2)
		ft_close(ms->out_fd);
	ft_close_pipes(ms);
	rl_clear_history();
	ft_cleanup_shell(ms);
	exit(exit_code);
}

void	ft_handle_heredoc_eof(t_ms *ms, int fd)
{
	printf("%s\nexit\n", ERROR_TOKEN);
	ft_close(fd);
	if (ms->doc_list)
	{
		ft_free_token_list(ms->doc_list);
		ms->doc_list = NULL;
	}
	if (ms->cache)
	{
		free(ms->cache);
		ms->cache = NULL;
	}
	rl_clear_history();
	ft_cleanup_shell(ms);
	exit(3);
}
