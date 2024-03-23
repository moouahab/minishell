/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouahab <mohamed.ouahab1999@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:20:12 by moouahab          #+#    #+#             */
/*   Updated: 2024/03/15 08:45:21 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	free_tab2(char **strs)
{
	size_t	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	strs = NULL;
}

char	*test_paths(char *cmd, char **paths_env_var)
{
	char	*path;
	size_t	i;

	i = 0;
	path = NULL;
	while (paths_env_var[i])
	{
		if (paths_env_var[i][ft_strlen(paths_env_var[i]) - 1] != '/')
			paths_env_var[i] = ft_strjoin(paths_env_var[i], ft_strdup("/"));
		path = ft_strjoin(ft_strdup(paths_env_var[i]), ft_strdup(cmd));
		if (access(path, F_OK) == 0)
		{
			free_tab2(paths_env_var);
			return (path);
		}
		i++;
		free(path);
	}
	free_tab2(paths_env_var);
	return (NULL);
}

static char	*check_for_file(char *cmd)
{
	struct stat	path_stat;

	if (lstat(cmd, &path_stat) == 0)
	{
		if (S_ISREG(path_stat.st_mode))
		{
			if (access(cmd, F_OK | X_OK) == 0)
				return (ft_strdup(cmd));
		}
		// else if (S_ISDIR(path_stat.st_mode) && ft_strchr(cmd, '/'))
		// 	return (ft_strdup("dir"));
	}
	// else if (ft_strchr(cmd, '/'))
	// {
	// 	if (access(cmd, F_OK) == -1)
	// 		return (ft_strdup("undir"));
	// }
	return (NULL);
}

char	*get_path(char *cmd, t_env *env)
{
	char		*path;
	char		**paths_env_var;

	if (!cmd)
		return (NULL);
	path = check_for_file(cmd);
	if (path)
		return (path);
	paths_env_var = ft_split(ft_getenv("PATH", env), ":");
	if (!paths_env_var)
		return (NULL);
	path = test_paths(cmd, paths_env_var);
	if (path)
		return (path);
	return (NULL);
}
