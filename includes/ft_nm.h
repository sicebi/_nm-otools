/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antini <antini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 10:53:07 by antini            #+#    #+#             */
/*   Updated: 2019/08/19 12:18:20 by antini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <mach-o/fat.h>
#include <fcntl.h>
# include "../libft/libft.h"

typedef struct			s_vars
{
	char				**sec;
}						t_vars;

typedef struct			s_lst
{
	char				type;
	char				*name;
	char				*value;
	uintmax_t			cmp_val;
	struct s_lst		*next;
}						t_lst;


//64-bit
int						ft_handle_64(void *ptr);
int						ft_create_block_64(t_lst **lst, struct nlist_64 nlist64,char **sections, char *stringtable);
//32-bit
int						ft_handle_32(void *ptr);
int						ft_create_block_32(t_lst **lst, struct nlist list, char **sections, char *stringtable);

// BOTH
int						ft_nm(void *ptr);
char					*ft_add_precision(uintmax_t value, int is64bit);
char					ft_type(uint8_t type, uintmax_t value, uint8_t sect, char **sections);
void					print_out(t_lst *lst, int is64bit);

#endif
