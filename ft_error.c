/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhasni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/09 06:27:37 by hhasni            #+#    #+#             */
/*   Updated: 2015/07/09 06:27:40 by hhasni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

int			ft_failure_error(char *s1, char *s2, char *s3)
{
	write(1, s1, ft_strlen(s1));
	write(1, s2, ft_strlen(s2));
	write(1, s3, ft_strlen(s3));
	write(1, "\n", 1);
	return (EXIT_FAILURE);
}

void		ft_void_error(char *s1)
{
	write(1, s1, ft_strlen(s1));
	write(1, "\n", 1);
	return ;
}
