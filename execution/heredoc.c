/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:30:50 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/17 10:30:52 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	is_heredoc_end(char *input, char *filename, int fd, char *lim)
{
	if (g_signum == SIGINT)
	{
		unlink(filename);
		close(fd);
		return (TRUE);
	}
	if (!input)
	{
		printf("minishell: warning: here-document ");
		printf("delimited by end-of-file (wanted `%s')\n", lim);
		return (TRUE);
	}
	if (!ft_strcmp(input, lim))
	{
		free(input);
		return (TRUE);
	}
	return (FALSE);
}

void	get_line(char *lim, int fd, t_shell *shell, char *filename)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, sigint_heredoc);
		input = readline("heredoc> ");
		dup2(shell->stdin_b, STDIN_FILENO);
		signal(SIGINT, sigint_handler);
		if (is_heredoc_end(input, filename, fd, lim))
			break ;
		input = expand(input, shell->env, shell);
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
}

char	*ft_tmpfilename(void)
{
	static int	i;
	char		filename[50];
	int			fd;

	fd = -2;
	if (i == 120)
		i = 1;
	while (fd != -1)
	{
		ft_bzero(filename, sizeof(filename));
		ft_memset(filename, i + 1, sizeof(filename));
		filename[49] = '\0';
		filename[0] = '.';
		if (fd >= 0)
			close(fd);
		fd = open(filename, O_RDONLY);
		i++;
	}
	return (ft_strdup(filename));
}

t_cmd	*new_heredoc(t_cmd *new, t_word **words, t_shell *shell)
{
	int		heredoc_fd;
	char	*tmpfile;

	if (new->typein == RD_AP_IN)
		unlink(new->filein);
	if (new->filein)
	{
		free(new->filein);
		new->filein = NULL;
	}
	tmpfile = ft_tmpfilename();
	heredoc_fd = open(tmpfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	get_line((*words)->next->word, heredoc_fd, shell, tmpfile);
	new->filein = tmpfile;
	new->typein = RD_AP_IN;
	*words = (*words)->next;
	return (new);
}

t_cmd	*heredoc_manager(t_cmd *new, t_word *words, t_shell *shell)
{
	t_word	*cur_word;

	cur_word = words;
	new->filein = NULL;
	new->typein = -1;
	while (cur_word && cur_word->token != PIPE)
	{
		if (cur_word->token == RD_AP_IN)
			new = new_heredoc(new, &cur_word, shell);
		if (cur_word->token == RD_IN)
		{
			if (new->typein == RD_AP_IN)
				unlink(new->filein);
			if (new->filein)
			{
				free(new->filein);
				new->filein = NULL;
			}
			if (cur_word->next)
				new->filein = ft_strdup(cur_word->next->word);
		}
		cur_word = cur_word->next;
	}
	return (new);
}
