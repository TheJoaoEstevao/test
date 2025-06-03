/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:50:02 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 17:58:45 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_cleanup_heredoc(t_ms *sh)
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
	while (!access(filename, R_OK) && index++ < sh->doc_num)
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

void	ft_cleanup_and_exit(t_ms *sh, int exit_code)
{
	if (sh->in_fd > 2)
		ft_close(sh->in_fd);
	if (sh->out_fd > 2)
		ft_close(sh->out_fd);
	ft_close_pipes(sh);
	rl_clear_history();
	ft_cleanup_shell(sh);
	exit(exit_code);
}

void	ft_handle_heredoc_eof(t_ms *sh, int fd)
{
	printf("%s\nexit\n", ERROR_TOKEN);
	ft_close(fd);
	if (sh->doc_list)
	{
		ft_free_token_list(sh->doc_list);
		sh->doc_list = NULL;
	}
	if (sh->cache)
	{
		free(sh->cache);
		sh->cache = NULL;
	}
	rl_clear_history();
	ft_cleanup_shell(sh);
	exit(3);
}
