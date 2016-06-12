/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhasni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/09 06:28:11 by hhasni            #+#    #+#             */
/*   Updated: 2015/07/09 06:28:12 by hhasni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static char			ft_n_masks_extend(t_dt_lst *my, int sect)
{
	t_dt_lst		*tmp;

	tmp = my;
	while (tmp && tmp->i != sect)
		tmp = tmp->next;
	if (tmp && tmp->i == sect)
	{
		if (!ft_strcmp(tmp->str, SECT_DATA))
			return ('D');
		if (!ft_strcmp(tmp->str, SECT_BSS))
			return ('B');
		if (!ft_strcmp(tmp->str, SECT_TEXT))
			return ('T');
	}
	return ('S');
}

static char			ft_n_masks(int type, int value, int sect, t_dt_lst *my)
{
	char			c;
	int				res;

	c = 0;
	res = type & N_TYPE;
	if (res == N_UNDF && value)
		c = 'C';
	if (res == N_UNDF && !value)
		c = 'U';
	if (res == N_ABS)
		c = 'A';
	if (res == N_PBUD)
		c = 'U';
	if (res == N_SECT)
		c = ft_n_masks_extend(my, sect);
	if (res == N_INDR)
		c = 'I';
	if (type & N_STAB)
		c = 'Z';
	if (!(type & N_EXT) && c)
		c += 32;
	return (c);
}

static void			ft_build_nm(struct symtab_command *sc,
void *s, t_dt_lst *my, bool f)
{
	t_sort_list			*sort_l;
	unsigned int		i;
	struct nlist_64		*list;
	char				*str;

	i = 0;
	sort_l = NULL;
	list = s + sc->symoff;
	str = s + sc->stroff;
	while (i < sc->nsyms)
	{
		if (list[i].n_type != 60)
			ft_push_sort_back(&sort_l,
				ft_decimal_to_hexastr(list[i].n_value),
				ft_n_masks(list[i].n_type, list[i].n_value, list[i].n_sect, my),
				str + list[i].n_un.n_strx);
		i++;
	}
	ft_display_nm(sort_l, f);
	return ;
}

static void			ft_recover_sectname_nm(struct load_command *lc,
t_dt_lst **my)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	i = 0;
	seg = (struct segment_command_64*)lc;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	while (i < seg->nsects)
	{
		ft_push_back(my, sec->sectname);
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

void				ft_nm(void *src, bool flag)
{
	int						data_len;
	int						len;
	struct mach_header_64	*mach64;
	struct load_command		*lc;
	t_dt_lst				*my_list;

	my_list = NULL;
	mach64 = (struct mach_header_64 *)src;
	lc = src + sizeof(struct mach_header_64);
	data_len = mach64->ncmds;
	len = 0;
	while (len++ < data_len)
	{
		if (lc->cmd == LC_SEGMENT_64)
			ft_recover_sectname_nm(lc, &my_list);
		if (lc->cmd == LC_SYMTAB)
		{
			ft_build_nm((struct symtab_command *)lc, src, my_list, flag);
			len = data_len;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
