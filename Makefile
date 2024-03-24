NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = builtins env_utils execution parsing signals utils

OBJ_DIR = obj

SRC = builtins/export_utils.c builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c \
    builtins/pwd.c builtins/run.c builtins/unset.c \
    env_utils/env.c env_utils/env_utils.c env_utils/env_utils2.c \
    execution/redirections_utils.c execution/exec_errors.c execution/execute.c execution/exec_utils.c execution/heredoc.c \
    execution/redirections.c execution/check_directories.c execution/init_and_free.c execution/init_pipes.c execution/main.c execution/pipe_manager.c \
    parsing/expand.c parsing/expand_utils.c parsing/free_utils.c parsing/init_cmds.c \
    parsing/init_cmds_utils.c parsing/invalid_tokens.c parsing/parse.c parsing/tokenize.c parsing/tokenize_utils.c \
    signals/sighandlers.c signals/signals.c \
    utils/get_path.c utils/utils.c utils/utils2.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -Llibft/ -lft -lreadline

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Ilibft/ -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re