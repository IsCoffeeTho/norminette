/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lnklist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:14:03 by amenadue          #+#    #+#             */
/*   Updated: 2022/08/30 13:06:18 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../norminette.h"

lst	*new_lstitem(char *value)
{
	lst *item = (lst *) ft_calloc(1, sizeof(lst));
	if (!item)
		return (NULL);
	item->value = value;
	item->next = NULL;
	return (item);
}

void lst_push(lst **list, lst *item)
// add to back
{
	if (!list || !item)
		return ;
	if (!(*list))
	{
		*list = item;
		return ;
	}
	lst *curr = *list;
	while (curr)
	{
		if (!curr->next)
			break;
		curr = curr->next;
	}
	curr->next = item;
}

lst	*lst_pop(lst **list)
// take from back
{
	lst *curr;
	lst *prev;

	if (!list || !(*list))
		return (NULL);
	curr = *list;
	while (curr)
	{
		if (!curr->next)
			break;
		prev = curr;
		curr = curr->next;
	}
	if (prev)
		prev->next = NULL;
	return (curr);
}

void lst_unshift(lst **list, lst *item)
// add to front
{
	if (!list || !item)
		return ;
	if (!(*list))
		item->next = *list;
	*list = item;
}

lst	*lst_shift(lst **list)
// take from front
{
	lst *item;
	if (!list || !(*list))
		return (NULL);
	item = *list;
	*list = item->next;
	item->next = NULL;
	return (item);	
}
