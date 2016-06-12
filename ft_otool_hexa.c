/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhasni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/09 06:28:18 by hhasni            #+#    #+#             */
/*   Updated: 2015/07/09 06:28:19 by hhasni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

char				*ft_hexa_deuce(int nb)
{
	char			*new;
	int				i;
	int				mod;

	i = 0;
	mod = 0;
	if (!(new = (char *)malloc(sizeof(char) * 2 + 1)))
		return (NULL);
	while (i < 2)
		new[i++] = '0';
	new[i] = 0;
	if (nb < 0)
		nb += 256;
	while (nb > 0)
	{
		mod = nb % 16;
		if (mod > 9 && mod < 16)
			new[--i] = 87 + mod;
		else
			new[--i] = 48 + mod;
		nb /= 16;
	}
	return (new);
}

static void			ft_print_hexastr(char *str)
{
	if (str)
	{
		write(1, str, ft_strlen(str));
		write(1, " ", 1);
	}
}

char				*ft_check_color(int j)
{
	if (j == 0)
		return ("\033[1;30m");
	else if (j == 1)
		return ("\033[0;30m");
	else if (j == 2)
		return ("\033[0;31m");
	else if (j == 3)
		return ("\033[1;31m");
	else if (j == 4)
		return ("\033[0;33m");
	else if (j == 5)
		return ("\033[0;32m");
	else if (j == 6)
		return ("\033[0;35m");
	else if (j == 7)
		return ("\033[1;35m");
	else if (j == 8)
		return ("\033[0;34m");
	else if (j == 9)
		return ("\033[1;32m");
	else if (j == 10)
		return ("\033[1;33m");
	return (NULL);
}

void				ft_print_color(char *str, int j, bool flag)
{
	char			*tmp;

	if (flag)
	{
		if (!(tmp = ft_check_color(j)))
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
		ft_print_hexastr(str);
		write(1, "\033[0m", ft_strlen("\033[0m"));
	}
	else
		ft_print_hexastr(str);
}

void				ft_disp_otool(struct section_64 *sec, char *src, bool flag)
{
	unsigned int			j;
	unsigned int			i;
	long unsigned int		len;

	i = 0;
	j = 0;
	len = sec->addr;
	while (i < sec->size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				len += 16;
			ft_print_hexastr(ft_decimal_to_hexastr(len));
		}
		ft_print_color(ft_hexa_deuce(src[i]), j++, flag);
		if ((i + 1) < sec->size && (i + 1) % 16 == 0)
		{
			j = 0;
			write(1, "\n", 1);
		}
		i++;
	}
	write(1, "\n", 1);
}
