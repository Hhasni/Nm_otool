/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhasni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/09 06:27:55 by hhasni            #+#    #+#             */
/*   Updated: 2015/07/09 06:27:57 by hhasni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

void				ft_check_type(void *src, void (*ptr)(void *, bool), bool f)
{
	if (*(unsigned int *)src == MH_MAGIC_64)
		(*ptr)(src, f);
	else if (*(unsigned int *)src == FAT_CIGAM)
		ft_fat_loop(src, ptr, f);
	else
		return (ft_void_error("wrong format error"));
}

void				ft_open_n_mmap(char *str, void (*ptr)(void *, bool), bool f)
{
	struct stat		buf;
	void			*src;
	int				fd;

	src = NULL;
	fd = 0;
	if ((fd = open(str, O_RDONLY)) == -1)
		return (ft_void_error("open error"));
	if (fstat(fd, &buf) == -1)
		return (ft_void_error("fstat error"));
	if ((src = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_F)
		return (ft_void_error("mmap error"));
	ft_check_type(src, ptr, f);
	if ((munmap(src, buf.st_size)) != 0)
		return (ft_void_error("munmap error"));
	if (close(fd) == -1)
		return (ft_void_error("close error"));
}

void				ft_check_rainbow(char *str, bool *flag, int *i)
{
	if (!(ft_strcmp(str, "-rainbow")))
	{
		*flag = true;
		*i = 2;
	}
}

void				(*ft_check_exec(char *str, int *type))(void *, bool)
{
	if (!ft_strcmp(str, "./ft_nm"))
	{
		*type = 0;
		return (ft_nm);
	}
	*type = 1;
	return (ft_otool);
}

int					main(int ac, char **av)
{
	int				i;
	bool			flag;
	void			(*ptr)(void *, bool);
	int				type;

	flag = false;
	i = 1;
	type = 0;
	if (ac < 2)
	{
		return (ft_failure_error("Usage : ", av[0],
		" [ARG] [...]\n\t-rainbow\t rainbow mod"));
	}
	ft_check_rainbow(av[1], &flag, &i);
	if (!(ptr = ft_check_exec(av[0], &type)))
		return (EXIT_FAILURE);
	while (i < ac)
	{
		if (type == 1 || (type == 0 && ac > 2))
			ft_print_input(av[i], type);
		ft_open_n_mmap(av[i++], ptr, flag);
	}
	return (EXIT_SUCCESS);
}
