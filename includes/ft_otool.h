/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antini <antini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:06:05 by antini            #+#    #+#             */
/*   Updated: 2019/08/19 13:05:59 by antini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

#include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <mach-o/fat.h>
# include "../libft/libft.h"

typedef struct				s_vars
{
	int						env;
	short					count;
}							t_vars;

int							ft_otool(void *ptr); 
int							ft_handle_64(void *ptr, int r);
int							ft_handle_32(void *ptr, int r);
void						ft_add_precision(uintmax_t value, int is64bit);
void						print_byte_to_hex(char byte, uintmax_t x);

#endif
