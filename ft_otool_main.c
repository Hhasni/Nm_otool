/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhasni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/09 06:28:23 by hhasni            #+#    #+#             */
/*   Updated: 2015/07/09 06:28:24 by hhasni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void			ft_rec_sectname(struct load_command *lc,
void *src, bool flag)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	i = 0;
	seg = (struct segment_command_64*)lc;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sec->sectname, ST) && !ft_strcmp(sec->segname, "__TEXT"))
		{
			write(1, "(__TEXT,__text) section\n", 24);
			ft_disp_otool(sec, (char*)src + sec->offset, flag);
		}
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

void				ft_otool(void *src, bool flag)
{
	int						data_len;
	int						len;
	struct mach_header_64	*mh64;
	struct load_command		*lc;

	mh64 = (struct mach_header_64 *)src;
	lc = src + sizeof(struct mach_header_64);
	data_len = mh64->ncmds;
	len = 0;
	while (len++ < data_len)
	{
		if (lc->cmd == LC_SEGMENT_64)
			ft_rec_sectname(lc, src, flag);
		lc += lc->cmdsize / sizeof(void*);
	}
}
