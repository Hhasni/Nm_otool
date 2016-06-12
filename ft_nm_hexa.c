/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhasni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/09 06:28:05 by hhasni            #+#    #+#             */
/*   Updated: 2015/07/09 06:28:06 by hhasni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void			ft_print_nm(char *s1, char c, char *s2)
{
	if (c != 'U')
		write(1, s1, ft_strlen(s1));
	else
		write(1, "                ", 16);
	write(1, " ", 1);
	write(1, &c, 1);
	write(1, " ", 1);
	write(1, s2, ft_strlen(s2));
	write(1, "\n", 1);
}

static void			ft_print_color_nm(char *s1, char c, char *s2, int j)
{
	char			*tmp;

	while (j > 16)
		j -= 16;
	if (j < 2)
		j += 2;
	if (!(tmp = ft_check_color((j))))
	{
		if (j == 11)
			tmp = "\033[0;36m";
		else if (j == 12)
			tmp = "\033[1;34m";
		else if (j == 13)
			tmp = "\033[1;36m";
		else if (j == 14)
			tmp = "\033[0;37m";
		else
			tmp = "\033[1;37m";
	}
	write(1, tmp, ft_strlen(tmp));
	ft_print_nm(s1, c, s2);
	write(1, "\033[0m", ft_strlen("\033[0m"));
}

void				ft_display_nm(t_sort_list *list, bool flag)
{
	int				i;
	t_sort_list		*tmp;
	t_sort_list		*bkp;

	i = -1;
	while (++i < ft_list_len(list))
	{
		tmp = list;
		while (tmp && tmp->stat)
			tmp = tmp->next;
		bkp = tmp;
		while (tmp)
		{
			if (!tmp->stat && ft_strcmp(bkp->s2, tmp->s2) > 0)
				bkp = tmp;
			tmp = tmp->next;
		}
		if (flag)
			ft_print_color_nm(bkp->s1, bkp->c, bkp->s2, i);
		else
			ft_print_nm(bkp->s1, bkp->c, bkp->s2);
		bkp->stat = true;
	}
}

char				*ft_decimal_to_hexastr(unsigned long int nb)
{
	char			*new;
	int				i;
	int				mod;

	i = 0;
	mod = 0;
	if (!(new = (char *)malloc(sizeof(char) * 16 + 1)))
		return (NULL);
	while (i < 16)
		new[i++] = '0';
	new[i] = 0;
	while (nb)
	{
		mod = nb % 16;
		if (mod > 9 && mod < 17)
			new[--i] = 87 + mod;
		else
			new[--i] = 48 + mod;
		nb /= 16;
	}
	return (new);
}

void				ft_print_input(char *s1, int i)
{
	if (i == 0)
		write(1, "\n", 1);
	write(1, s1, ft_strlen(s1));
	write(1, ":\n", 2);
}
