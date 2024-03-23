/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:06:05 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/17 11:06:07 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	check_arg(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] != '-')
		return (TRUE);
	while (arg[i] && arg[i] == '-')
		i++;
	if (arg[i] && arg[i] != '-')
	{
		write(2, "minishell: cd: invalid option\n", 30);
		return (FALSE);
	}
	if (i > 2)
	{
		write(2, "minishell: cd: invalid option\n", 30);
		return (FALSE);
	}
	return (TRUE);
}

static int	check_update(char **cur_path, char (*new_pwd)[1024],
	char (*old_pwd)[1024], t_env	**env)
{
	if (chdir(*cur_path) == -1)
	{
		perror("minishell: cd");
		free(*cur_path);
		return (1);
	}
	getcwd(*new_pwd, sizeof(*new_pwd));
	if (ft_getenv("OLDPWD", *env))
		update_value(env, "OLDPWD", ft_strdup(*old_pwd));
	else
		add_env(env, ft_strdup("OLDPWD"), ft_strdup(*old_pwd));
	if (ft_getenv("PWD", *env))
		update_value(env, "PWD", ft_strdup(*new_pwd));
	else
		add_env(env, ft_strdup("PWD"), ft_strdup(*new_pwd));
	free(*cur_path);
	return (0);
}

int	check_err(char **argv, t_env *env)
{
	if (argv[1] && argv[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	if (!argv[1] && !ft_getenv("HOME", env))
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	return (0);
}

char	*handle_tilt(char *av, t_env	**env)
{
	char	*path;

	path = ft_strjoin(ft_strdup(ft_getenv("HOME", *env)), ft_strdup(av + 1));
	return (path);
}

int	bn_cd(char **argv, t_env *env)
{
	char	*cur_path;
	char	old_pwd[1024];
	char	new_pwd[1024];

	ft_bzero(old_pwd, sizeof(old_pwd));
	ft_bzero(new_pwd, sizeof(new_pwd));
	if (check_err(argv, env) == 1)
		return (1);
	getcwd(old_pwd, sizeof(old_pwd));
	if (!argv[1] && ft_getenv("HOME", env))
		cur_path = ft_strdup(ft_getenv("HOME", env));
	else if (check_arg(argv[1]) == FALSE)
		return (2);
	else if (!ft_strncmp("-", argv[1], 1) && ft_strlen(argv[1]) <= 2)
		cur_path = ft_strdup(ft_getenv("OLDPWD", env));
	else if (!ft_strncmp("~", argv[1], 1))
		cur_path = handle_tilt(argv[1], &env);
	else
		cur_path = ft_strdup(argv[1]);
	if (check_update(&cur_path, &new_pwd, &old_pwd, &env) == 1)
		return (1);
	return (0);
}
