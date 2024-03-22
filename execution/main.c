/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouahab <moouahab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:58:20 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/22 16:54:03 by moouahab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int		g_signum = 0;

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->path)
			free(cmds->path);
		if (cmds->filein)
			free(cmds->filein);
		if (cmds->av)
			free_tab2(cmds->av);
		free(cmds);
		cmds = tmp;
	}
}

void	exit_and_free(char *input, t_shell *shell, int status)
{
	rl_clear_history();
	free(input);
	free_env(&shell->env);
	free_env(&shell->env_cpy);
	if (shell->cmds)
		free_cmds(shell->cmds);
	close(shell->stdin_b);
	close(shell->stdout_b);
	free(shell);
	exit(status);
}

t_shell	*init_shell(char *const *envp)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	shell->env = init_env(envp);
	shell->env_cpy = env_cpy(shell->env);
	shell->stdin_b = dup(STDIN_FILENO);
	shell->stdout_b = dup(STDOUT_FILENO);
	shell->ret_value = 0;
	return (shell);
}

int	main(int ac, char **av, char *const *envp)
{
	char	*input;
	t_shell	*shell;

	if (ac > 1)
		return (127);
	(void)av;
	shell = init_shell(envp);
	shell->words = NULL;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		shell->cmds = NULL;
		input = readline("minishell$ ");
		handle_signals(input, shell);
		shell->words = parse(input, shell->env, shell);
		if (!shell->words)
			free_words(shell->words);
		else
		{
			shell->cmds = init_cmds(shell->words, shell);
			execute(shell->cmds, shell);
		}
	}
}
