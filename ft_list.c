/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhasni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/09 06:27:49 by hhasni            #+#    #+#             */
/*   Updated: 2015/07/09 06:27:50 by hhasni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

void		ft_push_back(t_dt_lst **lst, char *s1)
{
	t_dt_lst *new;
	t_dt_lst *tmp;

	tmp = NULL;
	if (!(new = (t_dt_lst*)malloc(sizeof(t_dt_lst))))
		return ;
	new->str = ft_strdup(s1);
	new->next = NULL;
	if (!*lst)
	{
		new->i = 1;
		*lst = new;
	}
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		new->i = tmp->i + 1;
		tmp->next = new;
	}
}

void		ft_push_sort_back(t_sort_list **list, char *s1, char c, char *s2)
{
	t_sort_list *new;
	t_sort_list *tmp;

	tmp = NULL;
	if (c == 'z' || c == 'Z')
		return ;
	if (!(new = (t_sort_list*)malloc(sizeof(t_sort_list))))
		return ;
	new->s1 = ft_strdup(s1);
	new->c = c;
	new->s2 = ft_strdup(s2);
	new->stat = false;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
