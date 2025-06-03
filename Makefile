# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 16:49:52 by jopedro3          #+#    #+#              #
#    Updated: 2025/06/03 13:50:25 by jestevao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -lreadline
INC = includes
SRC_DIR = src
OBJ_DIR = obj
NAME = minishell
CMD_FILES = ft_main ft_pwd ft_echo ft_env ft_cd ft_exit ft_unset ft_export ft_export_print
CLEAN_FILES = ft_clean_one ft_clean_two ft_clean_three ft_error ft_cleanup
ENV_FILES = ft_utils ft_env ft_envlst
EXEC_FILES = ft_exec ft_cmd ft_utils ft_path
EXP_FILES = ft_exp ft_arg ft_utils
HEREDOC_FILES = ft_utils ft_hdoc
TOKEN_FILES = ft_utils ft_token
PARSE_FILES = ft_utils ft_parse ft_prompt
SIG_FILES = ft_signal
UTILS_FILES = ft_str_one ft_mem ft_print ft_char ft_gen ft_more ft_str_two ft_main_util
FILES = ft_main \
        $(addprefix cmd/, $(CMD_FILES)) \
        $(addprefix clean/, $(CLEAN_FILES)) \
        $(addprefix env/, $(ENV_FILES)) \
        $(addprefix exec/, $(EXEC_FILES)) \
        $(addprefix exp/, $(EXP_FILES)) \
        $(addprefix heredoc/, $(HEREDOC_FILES)) \
        $(addprefix token/, $(TOKEN_FILES)) \
        $(addprefix parse/, $(PARSE_FILES)) \
        $(addprefix prompt/, $(PROMPT_FILES)) \
        $(addprefix sig/, $(SIG_FILES)) \
        $(addprefix utils/, $(UTILS_FILES))
SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))
DIRS = cmd clean env exec exp heredoc token parse prompt sig utils
OBJ_DIRS = $(addprefix $(OBJ_DIR)/, $(DIRS))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) -I $(INC)
	@echo "Ready to go!"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)/ft_minishell.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIRS)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo "Cleanup!"

re: fclean all

valgrind: fclean all
	valgrind --leak-check=full --show-leak-kinds=all -s \
	--trace-children=yes --track-fds=yes --log-file=output.log ./minishell

.PHONY: all clean fclean re valgrind
