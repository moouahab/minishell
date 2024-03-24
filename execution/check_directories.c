/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directories.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:22:37 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/24 11:22:38 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	is_regfile_with_slash(char *cmd)
{
	char		*tmp;
	struct stat	path_stat;

	if (cmd[ft_strlen(cmd) - 1] == '/')
	{
		tmp = ft_calloc(sizeof(char), ft_strlen(cmd));
		if (!tmp)
			return (NULL);
		ft_strlcpy(tmp, cmd, ft_strlen(cmd));
		if (lstat(tmp, &path_stat) == 0)
		{
			if (S_ISREG(path_stat.st_mode))
			{
				free(tmp);
				return (TRUE);
			}
		}
		free(tmp);
	}
	return (FALSE);
}

void	check_filetype(char *file)
{
	if (access(file, F_OK) == -1)
	{
		write(2, "minishell: no such file or directory: ", 38);
		write(2, file, ft_strlen(file));
		write(2, "\n", 1);
	}
	else
	{
		write(2, "minishell: ", 12);
		write(2, file, ft_strlen(file));
		write(2, ": is a directory\n", 17);
	}
}

bool	is_directory(char *filename)
{
	struct stat	path_stat;

	if (lstat(filename, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (TRUE);
	}
	return (FALSE);
}
