/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:31:03 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:31:04 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	is_quoted(char *input, size_t *i, char quote)
{
	size_t	j;

	j = *i + 1;
	if (!input[j])
		return (FALSE);
	while (input[j] && input[j] != quote)
		j++;
	if (!input[j])
		return (FALSE);
	*i = j;
	return (TRUE);
}

size_t	skip_spaces(char *input, size_t i, char dir)
{
	if (dir == '+')
	{
		while (input[i] && input[i] == ' ')
			i++;
	}
	else if (dir == '-')
	{
		while (i != 0 && input[i] == ' ')
			i--;
	}
	return (i);
}

t_word	*parse(char *input, t_env *env, t_shell *shell)
{
	char	c;
	t_word	*words;

	words = NULL;
	if (input && input[0])
	{
		c = check_invalid_tokens(input);
		if (!c)
		{
			add_history(input);
			input = expand(input, env, shell);
			words = tokenize(input);
		}
		else if (c == '\n')
			printf("minishell: syntax error near unexpected token 'newline'\n");
		else
		{
			shell->ret_value = 2;
			printf("minishell: syntax error near unexpected token '%c'\n", c);
		}
	}
	free(input);
	return (words);
}
