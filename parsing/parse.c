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
		while (input[i] && is_whitespace(input[i]))
			i++;
	}
	else if (dir == '-')
	{
		while (i != 0 && is_whitespace(input[i]))
			i--;
	}
	return (i);
}

void	print_syntax_errors(char c, t_shell *shell)
{
	if (c == '\n')
	{
		shell->ret_value = 2;
		printf("minishell: syntax error near unexpected token 'newline'\n");
	}
	else if (c == 2)
	{
		shell->ret_value = 2;
		printf("minishell: syntax error near unexpected token '>>'\n");
	}
	else if (c == 3)
	{
		shell->ret_value = 2;
		printf("minishell: syntax error near unexpected token '<<'\n");
	}
	else
	{
		shell->ret_value = 2;
		printf("minishell: syntax error near unexpected token '%c'\n", c);
	}
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
		else
			print_syntax_errors(c, shell);
	}
	free(input);
	return (words);
}
