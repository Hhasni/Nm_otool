/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmotool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhasni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/09 06:28:32 by hhasni            #+#    #+#             */
/*   Updated: 2015/07/09 06:28:33 by hhasni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NMOTOOL_H
# define NMOTOOL_H

# include <stdlib.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <mach-o/ranlib.h>
# include <ar.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>

# define ST	SECT_TEXT
# define S_C symtab_command
# define MAP_F MAP_FAILED

typedef struct				s_data_list
{
	int						i;
	char					*str;
	struct s_data_list		*next;
}							t_dt_lst;

typedef struct				s_sort_list
{
	char					*s1;
	char					c;
	bool					stat;
	char					*s2;
	struct s_sort_list		*next;
}							t_sort_list;

char						*ft_strdup(char *str);
int							ft_strcmp(char *s1, char *s2);
int							ft_strlen(char *s);
int							ft_list_len(t_sort_list *list);
void						ft_push_back(t_dt_lst **lst, char *s1);
void						ft_push_sort_back(t_sort_list **list, char *s1,
							char c, char *s2);
char						*ft_decimal_to_hexastr(unsigned long int nb);
char						*ft_hexa_deuce(int nb);
int							ft_failure_error(char *s1, char *s2, char *s3);
void						ft_void_error(char *s1);
void						ft_display_nm(t_sort_list *list, bool flag);
void						ft_disp_otool(struct section_64	*sec,
							char *src, bool flag);
void						ft_print_rainbow(char *s1, int i);
void						ft_print_input(char *s1, int i);
void						ft_check_type(void *src, void (*ptr)(void *, bool),
							bool flag);
void						ft_open_n_mmap(char *str, void (*ptr)(void *, bool),
							bool flag);
void						ft_nm(void *src, bool flag);
void						ft_otool(void *src, bool flag);
char						*ft_check_color(int j);
void						ft_fat_loop(void *src, void (*ptr)(void *, bool),
							bool flag);

#endif
