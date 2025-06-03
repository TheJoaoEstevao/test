/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:49:47 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/02 17:47:01 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum s_enums
{
	TOK_WORD,
	TOK_PIPE,
	TOK_RED_OUT,
	TOK_APPEND,
	TOK_RED_IN,
	TOK_HEREDOC,
}	t_enums;

typedef struct s_token
{
	char			*content;
	t_enums			kind;
	int				index;
	char			*limit;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_track
{
	int	cursor;
	int	phrase;
	int	amount;
	int	d_quote;
	int	s_quote;
}	t_track;

typedef struct s_var
{
	char			*name;
	char			*value;
	int				scope;
	struct s_var	*next;
}	t_var;

typedef struct s_cmd
{
	int				mode;
	char			**cmds;
	t_token			*io;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_cmd;

typedef struct s_ms
{
	char			*buff;
	char			*display;
	char			*home;
	char			*cache;
	char			**context;
	char			***matrix;
	int				code;
	int				doc_num;
	int				doc_state;
	int				b_l;
	int				processed;
	int				exec_num;
	int				**channels;
	int				in_fd;
	int				out_fd;
	int				line_count;
	t_var			*locals;
	t_token			*sequence;
	t_cmd			*syntax;
	t_track			*track;
	t_token			*doc_list;
	pid_t			process;
}	t_ms;

# define DELIMS        "\t\n\v\f\r "
# define SYNTAX_CHARS  "|></ \t\n\v\f\r"
# define OP_CHARS      "<>|"
# define MS_PREFIX     "[minishell]"
# define HDOC_EOF_WARN "[minishell]: warning: here-doc delimited by \
end-of-file (wanted"
# define ERROR_TOKEN   "[minishell]: syntax error near unexpected token\n"
# define ERROR_EOF     "[minishell]: syntax error: unexpected end of file"
# define INV_IDENT     "': not a valid identifier"
# define MAX_LLONG_STR	"9223372036854775807"
# define MIN_LLONG_STR	"9223372036854775808"
# define TEMP_NFS       ".nfs01sdfdfsdf3f1dca2zx"
# define BUFFER_SIZE    1024
# define CMD_TYPE       2

void		ft_expand_hdoc_vars(t_ms *ms, char *tmp, char **line);
int			ft_check_input_redirection(t_ms *ms, t_token *temp);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
size_t		ft_strlen_matrix(char **s);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isspace(int c);
long		ft_atol(const char *str);
int			ft_is_str_equal(const char *s1, const char *s2);
char		*ft_nl_strjoin(char *s1, char *s2);
int			ft_count_words(char const *s, char c);
void		ft_process_redirect_heredoc(t_ms *ms, t_token **in_redirs);

char		*ft_itoa(int n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
void		ft_putendl_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_gnl(int fd);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		ft_handle_redirections(t_ms *ms, t_cmd *node);
void		ft_close(int fd);
void		ft_close_all_fds(void);
char		*ft_safe_getcwd(t_ms *ms, int error_code);
void		ft_handle_exit(t_ms *ms);
void		ft_check_empty_line(t_ms *ms);
char		*ft_get_prompt(t_ms *ms);
t_token		*ft_create_token_node(char *content, int index, t_ms *ms);
void		ft_add_token_back(t_token **lexer, t_token *new);
t_token		*ft_tokenize_input(char *ui, t_ms *ms);
t_bool		ft_is_present(const char *str, char c);
int			ft_get_token_type(char *word, t_ms *ms);
void		ft_set_word_end(char *ui, t_ms *ms);
t_cmd		*ft_create_cmd_node(t_token **start, t_token *end, t_ms *ms);
void		ft_convt_list_to_array(t_token *start, t_token *end, char ***cmd);
t_cmd		*ft_build_cmd_tree(t_token **start, t_ms *ms);
void		ft_rm_quotes_hdoc(char *str);
void		ft_check_hdoc(t_token *lexer, t_ms *ms);
char		*ft_strstr(char *haystack, char *needle);
int			ft_remove_null_entries(char **cmds, int count);
int			ft_expand_command_str(char *value, int start, int end, char **line);
void		ft_handle_valid_env(int pos, t_ms *ms, char *env_val, char **line);
int			ft_expand_and_free(char *name, int start, int end, char **line);
int			ft_expand_dollar(t_ms *ms, int point, char *tmp, char **line);
int			ft_check_quote_pairs(const char *str, t_ms *ms);
void		ft_expand_env_vars(t_ms *ms, char *tmp, char **line);
void		ft_update_command_array(t_ms *ms, char *value, char **line);
void		ft_space_pipes(t_ms *ms, char *tmp);
void		ft_expand_commands(char ***cmds, t_ms *ms);
char		*ft_trim_spaces(t_ms *ms, char *str);
void		ft_handle_child_signal(int signo);
void		ft_setup_signals(void);
void		ft_update_exit_status(t_ms *ms, int status);
void		ft_handle_hdoc_signal(int signo);
char		*ft_strtok(char *str, char *delimiter);
t_bool		ft_check_command(t_ms *ms, char **cmds);
void		ft_execute_command(t_ms *ms, char **cmds);
void		ft_cmd_error_exit(t_ms *ms, const char *cmd,
				int err_no, char *path);
void		ft_create_pipes(t_ms *ms);
void		ft_close_pipes(t_ms *ms);
t_bool		ft_is_absolute_path(char *path);
char		*ft_find_command_path(char *cmd, t_ms *ms);
void		ft_handle_null_path(t_ms *ms, char **cmds);
void		ft_executor(t_ms *ms, t_cmd *parser, int i);
int			ft_cd(t_ms *ms, char **cmds);
int			ft_echo(char **cmds);
int			ft_env(t_ms *ms, char **cmds);
void		ft_exit(t_ms *ms, char **cmds);
int			ft_export(t_ms *ms, char **cmds);
void		ft_export_print(t_ms *ms);
int			ft_pwd(t_ms *ms);
int			ft_unset(t_ms *ms, char **cmds);
t_bool		ft_is_parent(char **cmd);
t_bool		ft_is_child(char **cmd);
int			ft_route(t_ms *ms, char **cmds);
t_var		*ft_create_env_node(char *name, char *value, int visible);
char		*ft_extract_env_name(char *mini_env);
void		ft_free_token_list(t_token *head);
void		ft_free_str_array(char **matrix);
void		ft_free_pipe_array(t_ms *ms);
void		ft_cleanup_heredoc(t_ms *ms);
void		ft_free_cmd_tree(t_cmd *home);

void		ft_cleanup_and_exit(t_ms *ms, int i);
void		ft_handle_heredoc_eof(t_ms *ms, int fd);
t_bool		ft_check_operator_sequence(t_token *lexer);
int			ft_validate_syntax(t_token *lexer);
void		ft_error_msg(char *s1, char *s2, char *s3, char *s4);
t_bool		ft_check_empty_redirect(t_token *lexer);
void		ft_syntax_error(char *token, t_ms *ms);
void		ft_print_syntax_error(char *token);
t_bool		ft_process_tokens(t_ms *ms);
t_bool		ft_validate_final_syntax(t_token *curr, t_ms *ms);
t_bool		ft_check_token_sequence(t_token *curr, t_ms *ms);
t_bool		ft_is_empty_line(char *str);
char		*ft_extract_env_value(char *mini_env);
void		ft_init_env_list(t_ms *ms);
void		ft_free_env_list(t_var *env_lst);
void		ft_free_env_node(t_var *node);
char		**ft_copy_env_array(char **envp);
void		ft_append_env_node(t_var **head, t_var *new_node);
void		ft_update_env_array(t_ms *ms);
char		*ft_get_env_value(t_ms *ms, char *name);
int			ft_update_env_value(t_ms *ms, char *name, char *new_value);
void		ft_reset_shell_state(t_ms *ms);
void		ft_init_shell_vars(t_ms *ms);
void		ft_cleanup_shell(t_ms *ms);
void		ft_delete_token_pair(t_token **lexer, int name);
void		ft_create_heredoc(t_token *heredoc_node, t_ms *ms);
void		ft_delete_token(t_token *node);

extern int	g_signo;

#endif
