/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:57:28 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:57:29 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

extern int			g_signum;

typedef enum e_token
{
	PIPE,
	RD_IN,
	RD_OUT,
	RD_AP_IN,
	RD_AP_OUT,
	RD_FILE,
	WORD,
	CMD,
	ARG
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_word
{
	char			*word;
	t_token			token;
	struct s_word	*next;
	struct s_word	*prev;
}					t_word;

typedef struct s_cmd
{
	char			**av;
	char			*path;
	int				fdout;
	int				fdin;
	char			*filein;
	t_token			typein;
	t_token			typeout;
	size_t			i;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	int				**pfd;
	size_t			pipe_count;
	t_env			*env;
	t_env			*env_cpy;
	char			**envp;
	t_cmd			*cmds;
	pid_t			*ids;
	t_word			*words;
	int				stdin_b;
	int				stdout_b;
	int				ret_value;
}					t_shell;

// env utils :
int					free_env(t_env **env);
int					update_value(t_env **env, char *key, char *value);
int					delone_env(t_env **env, char *key);
void				free_node(t_env *node);
int					add_env(t_env **env, char *key, char *value);

// env :
t_env				*init_env(char *const *env);
char				*ft_getenv(char *key, t_env *env);
char				*get_key(char *env_str);
char				*get_value(char *env_str);

// signals :
void				sigint_handler(int signum);
void				handle_signals(char *input, t_shell *shell);

// invalid tokens :
int					check_invalid_tokens(char *input);
bool				is_quoted(char *input, size_t *i, char quote);
size_t				skip_spaces(char *input, size_t i, char dir);

// expand :
char				*expand(char *input, t_env *env, t_shell *shell);

// expand utils :
char				*del_char(char *s, size_t i);
void				get_quote_state(char c, bool *is_in_single,
						bool *is_in_double);
bool				is_limiter(char *input, size_t i, bool is_in_double);

// parsing :
t_word				*parse(char *input, t_env *env, t_shell *shell);

// tokenize :
t_word				*tokenize(char *input);

// tokenize utils :
int					add_word(t_word **words, char *word, int token);
void				free_words(t_word *words);
int					update_word(t_word *word, char *new_word);
int					get_operator_token(char *word);

// init cmds :
t_cmd				*init_cmds(t_word *words, t_shell *shell);

// init cmds utils :
t_word				*skip_rd_and_file(t_word *current);
t_word				*go_to_next_pipe(t_word *current);
char				**get_av(t_word *words);
void				free_cmds(t_cmd *cmds);

// utils :
size_t				ft_strlen_c(const char *s, char c);
size_t				ft_strlen_sep(const char *s, char *sep);
bool				is_operator(char c);
bool				is_quote(char c);
bool				is_redirector(char c);
size_t				ft_strlen2(char **strs);
char				*get_path(char *cmd, t_env *env);
void				free_tab2(char **strs);
void				exit_and_free(char *input, t_shell *shell, int status);
int					ft_strcmp(char *s1, char *s2);
t_env				*env_cpy(t_env *env);
void				sort_env(t_env **env);
bool				is_in_env(char *key, t_env *env);

// signals :
void				sigint_handler(int signum);
void				sigint_handler2(int signum);
void				sigint_heredoc(int signum);
void				sigquit_handler(int signum);
void				sigquit_handler2(int signum);

// exec_errors :
int					is_unknown_cmd(t_cmd *cmd, t_shell *shell, bool is_forked);

// redirections_utils :
t_cmd				*get_out_rds(t_cmd *cmd, t_word *current, t_shell **shell);
int					check_in(t_cmd **cmd, t_word *current, t_shell **shell);
void				check_filetype(char *file);
bool				can_rd_out(char *filename);

// execute :
void				execute(t_cmd *cmds, t_shell *shell);
t_cmd				*heredoc_manager(t_cmd *new, t_word *words, t_shell *shell);
t_cmd				*get_redirections(t_cmd *cmd, t_word *words,
						t_shell **shell);
void				pipe_manager(t_shell *shell, size_t i);
void				wait_for_children(t_shell *shell, pid_t *ids);
t_shell				*init_exec(t_shell *shell, t_cmd *cmds);
void				free_exec(t_shell *shell, t_cmd *cmds);

// exec_utils :
bool				is_builtin(char *cmd);
size_t				get_env_len(t_env *env);
char				**get_env_tab(t_env *env);
int					exec_builtin(char **av, t_shell *shell, bool is_forked);
void				redirect(t_cmd *cmd, t_shell *shell, bool is_forked);
void				exitchild_and_free(t_shell *shell, int e_status);
void				close_heredoc(t_cmd *cmd);
bool				is_directory(char *filename);
void				free_and_close_backup(t_shell *shell);

// init_pipes :
size_t				count_pipes(t_cmd *cmds);
void				free_pipes(int **pfd, size_t pipe_count);
int					**init_pipes(t_cmd *cmds);

// builtins :
int					bn_cd(char **argv, t_env *env);
int					bn_echo(char **argv);
int					bn_env(char **argv, t_env *env);
int					bn_pwd(char **av, t_env *env);
int					bn_unset(char **argv, t_shell *shell);
int					bn_export(char **argv, t_shell *shell);
int					bn_exit(char **av, t_shell *shell, bool is_forked);
int					run(char **av, t_shell *shell);

#endif
