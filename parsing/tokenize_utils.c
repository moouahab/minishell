/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:31:24 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:31:25 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	add_word(t_word **words, char *word, int token)
{
	t_word	*new;
	t_word	*head;

	if (!word)
		return (EXIT_FAILURE);
	new = ft_calloc(sizeof(t_word), 1);
	if (!new)
		return (EXIT_FAILURE);
	new->word = word;
	new->token = token;
	new->next = NULL;
	if (!*words)
	{
		*words = new;
		new->prev = NULL;
		return (EXIT_SUCCESS);
	}
	head = *words;
	while ((*words)->next)
		*words = (*words)->next;
	(*words)->next = new;
	new->prev = (*words);
	(*words) = head;
	return (EXIT_SUCCESS);
}

int	update_word(t_word *word, char *new_word)
{
	t_word	*current;

	current = word;
	if (!new_word)
		return (EXIT_FAILURE);
	while (current->next)
		current = current->next;
	free(current->word);
	current->word = new_word;
	return (EXIT_SUCCESS);
}

int	get_operator_token(char *word)
{
	if (!ft_strcmp(word, "|"))
		return (PIPE);
	if (!ft_strcmp(word, ">"))
		return (RD_OUT);
	if (!ft_strcmp(word, "<"))
		return (RD_IN);
	if (!ft_strcmp(word, ">>"))
		return (RD_AP_OUT);
	if (!ft_strcmp(word, "<<"))
		return (RD_AP_IN);
	return (-1);
}
