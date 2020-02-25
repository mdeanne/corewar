/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:16:19 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/04 19:16:21 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "blackbox_memlist.h"

t_ml_lists	*add_ml_list(uint32_t list_num, t_ml_lists **cur)
{
	t_ml_lists	*new;

	if (!(new = (t_ml_lists*)malloc(sizeof(t_ml_lists))))
		go_exit("ERROR: can't alloc memory");
	new->list_num = list_num;
	new->list = NULL;
	new->next = NULL;
	if (!*cur)
	{
		*cur = new;
		new->prev = NULL;
	}
	else if (!(*cur)->next)
	{
		(*cur)->next = new;
		new->prev = *cur;
	}
	else
	{
		new->prev = (*cur)->prev;
		new->next = *cur;
		(*cur)->prev->next = new;
		(*cur)->prev = new;
	}
	return (new);
}

t_ml		*ml_create(void *ptr)
{
	t_ml *new;

	new = NULL;
	if (!(new = (t_ml*)malloc(sizeof(t_ml))))
		return (NULL);
	new->data = ptr;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

_Bool		ml_push_front(t_ml **head, t_ml *new)
{
	if (!new)
	{
		ml_clear_lst(head);
		return (0);
	}
	if (head && *head)
	{
		new->next = *head;
		(*head)->prev = new;
	}
	*head = new;
	return (1);
}
