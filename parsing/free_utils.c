/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:30:26 by rbenoit           #+#    #+#             */
/*   Updated: 2024/03/15 08:30:27 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	free_words(t_word *words)
{
	t_word	*tmp;

	if (!words)
		return ;
	while (words)
	{
		tmp = words->next;
		free(words->word);
		words->next = NULL;
		free(words);
		words = tmp;
	}
	words = NULL;
}
