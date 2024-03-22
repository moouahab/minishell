/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:37:44 by rbenoit           #+#    #+#             */
/*   Updated: 2023/11/16 10:45:33 by rbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;
	int		lst_size;

	tmp = lst;
	lst_size = ft_lstsize(lst);
	while (lst_size > 1)
	{
		tmp = tmp->next;
		lst_size--;
	}
	return (tmp);
}
