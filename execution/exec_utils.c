/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:30:41 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/17 10:30:42 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (TRUE);
	if (!ft_strcmp(cmd, "env"))
		return (TRUE);
	if (!ft_strcmp(cmd, "pwd"))
		return (TRUE);
	if (!ft_strcmp(cmd, "unset"))
		return (TRUE);
	if (!ft_strcmp(cmd, "export"))
		return (TRUE);
	if (!ft_strcmp(cmd, "exit"))
		return (TRUE);
	if (!ft_strcmp(cmd, "cd"))
		return (TRUE);
	if (!ft_strncmp(cmd, "./", 2) && cmd[2])
		return (TRUE);
	return (FALSE);
}

size_t	get_env_len(t_env *env)
{
	t_env	*current;
	size_t	len;

	len = 0;
	current = env;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

char	**get_env_tab(t_env *env)
{
	t_env	*current;
	char	**env_tab;
	size_t	len;
	size_t	i;

	len = get_env_len(env);
	if (len == 0)
		return (NULL);
	env_tab = ft_calloc(sizeof(char *), len + 1);
	if (!env_tab)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		env_tab[i] = ft_strjoin(ft_strdup(current->key), ft_strdup("="));
		env_tab[i] = ft_strjoin(env_tab[i], ft_strdup(current->value));
		i++;
		current = current->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

int	exec_builtin(char **av, t_shell *shell, bool is_forked)
{
	int	e_status;

	e_status = 0;
	if (!ft_strcmp(av[0], "echo"))
		e_status = bn_echo(av);
	if (!ft_strcmp(av[0], "env"))
		e_status = bn_env(av, shell->env);
	if (!ft_strcmp(av[0], "pwd"))
		e_status = bn_pwd(av, shell->env);
	if (!ft_strcmp(av[0], "unset"))
		e_status = bn_unset(av, shell);
	if (!ft_strcmp(av[0], "export"))
		e_status = bn_export(av, shell);
	if (!ft_strcmp(av[0], "cd"))
		e_status = bn_cd(av, shell->env);
	if (!ft_strcmp(av[0], "exit"))
		e_status = bn_exit(av, shell, is_forked);
	if (!ft_strncmp(av[0], "./", 2) && av[0][2])
		e_status = run(av, shell);
	return (e_status);
}

void	free_and_close_backup(t_shell *shell)
{
	free_words(shell->words);
	close(shell->stdin_b);
	close(shell->stdout_b);
}
