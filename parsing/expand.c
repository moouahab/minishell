/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:30:05 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:38:00 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*replace_value(char *str, char *value, size_t start, size_t len)
{
	char	*res;

	if (str[start] == '?')
		len = 1;
	else
	{
		while (str[start + len] && !is_whitespace(str[start + len]) && str[start
				+ len] != '\'' && str[start + len] != '\"'
			&& str[start + len] != '$')
		{
			if (!ft_isalpha(str[start + len]) && str[start + len] != '_')
				break ;
			len++;
		}
	}
	res = ft_calloc(sizeof(char), ft_strlen(str) - len + ft_strlen(value) + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, start);
	ft_strlcat(res, value, ft_strlen(res) + ft_strlen(value) + 1);
	ft_strlcat(res, str + start + len, ft_strlen(res) + ft_strlen(str + start
			+ len) + 1);
	free(str);
	return (res);
}

void	get_user_var_len(char *input, size_t *i, size_t *j)
{
	if (input[*j] == '?')
	{
		(*i)++;
		(*j)++;
	}
	while (input[*j] && !is_whitespace(input[*j]) && input[*j] != 39 && input[*j] != 34
		&& (ft_isalnum(input[*j]) || input[*j] == '_'))
	{
		(*i)++;
		(*j)++;
	}
}

char	*get_user_var(char *input, size_t index)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	index++;
	j = index;
	get_user_var_len(input, &i, &j);
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (j < i)
		res[j++] = input[index++];
	res[j] = '\0';
	return (res);
}

char	*do_expand(char *input, size_t *i, t_env *env, t_shell *shell)
{
	char	*user_var;
	char	*ret_value;

	user_var = get_user_var(input, *i);
	if (!user_var)
		return (NULL);
	if (input[*i + 1] && input[*i + 1] == '?')
	{
		ret_value = ft_itoa(shell->ret_value);
		input = replace_value(input, ret_value, *i + 1, 1);
		free(ret_value);
	}
	else
		input = replace_value(input, ft_getenv(user_var, env), *i + 1, 1);
	if (!input)
	{
		free(user_var);
		return (NULL);
	}
	free(user_var);
	if (input[*i] == '$' || input[*i] == '\'' || input[*i] == '\"')
		(*i)--;
	return (input);
}

char	*expand(char *input, t_env *env, t_shell *shell)
{
	size_t	i;
	bool	is_in_single;
	bool	is_in_double;

	i = 0;
	is_in_single = false;
	is_in_double = false;
	while (input[i])
	{
		get_quote_state(input[i], &is_in_single, &is_in_double);
		if (input[i] == '$' && input[i + 1] && is_quote(input[i + 1])
			&& !is_in_double && !is_in_single && !is_limiter(input, i,
				is_in_double))
			input = del_char(input, i);
		if (input[i] == '$' && input[i + 1] && !is_whitespace(input[i + 1]) && input[i
				+ 1] != '$' && (ft_isalnum(input[i + 1]) || input[i + 1] == '?' || input[i + 1] == '_')&& !is_quote(input[i + 1]) && !is_in_single
			&& !is_limiter(input, i, is_in_double))
			input = do_expand(input, &i, env, shell);
		i++;
	}
	shell->ret_value = 0;
	return (input);
}
