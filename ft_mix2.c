/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhasni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/09 06:27:55 by hhasni            #+#    #+#             */
/*   Updated: 2015/07/09 06:27:57 by hhasni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static uint32_t		swap_uint32(uint32_t val)
{
	return (((val << 24) & 0xFF000000) |
		((val << 8) & 0x00FF0000) |
		((val >> 8) & 0x0000FF00) |
		((val >> 24) & 0x000000FF));
}

void				ft_fat_loop(void *src, void (*ptr)(void *, bool), bool flag)
{
	int					data_len;
	int					len;
	struct fat_header	*fh;
	struct fat_arch		*fa;

	fh = (struct fat_header	*)src;
	data_len = swap_uint32(fh->nfat_arch);
	fa = (void*)src + sizeof(fh);
	len = 0;
	while (len++ < data_len)
	{
		if (swap_uint32(fa->cputype) == CPU_TYPE_X86_64)
			ft_check_type(src + swap_uint32(fa->offset), ptr, flag);
		fa += sizeof(fa) / sizeof(void*);
	}
}
