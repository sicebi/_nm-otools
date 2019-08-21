/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antini <antini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 10:55:57 by antini            #+#    #+#             */
/*   Updated: 2019/08/19 12:20:13 by antini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			block_64(struct nlist_64 list, char *t, t_vars vars, t_lst **lst)
{
	if (ft_create_block_64(lst, list, vars.sec, t))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	get_sym_64(struct symtab_command *sym, void *ptr, t_vars vars)
{
	uint32_t				i;
	char					*stringtable;
	struct nlist_64			*array;
	t_lst					*lst;

	i = 0;
	lst = NULL;
	array = ptr + sym->symoff;
	stringtable = ptr + sym->stroff;
	while (i < sym->nsyms)
	{
		if (!(array[i].n_type & N_STAB))
			if (block_64(array[i], stringtable, vars, &lst))
				return (EXIT_FAILURE);
		i++;
	}
	free(vars.sec);
	print_out(lst, 1);
	return (EXIT_SUCCESS);
}

static char	**sec_64(char **sections, struct segment_command_64 *lc)
{
	struct section_64		*sec;
	char					**tmp;
	uint32_t				i;
	uint32_t				j;

	i = 0;
	j = 0;
	if (lc->nsects < 1)
		return (sections);
	while (sections && sections[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (lc->nsects + i + 1));
	tmp[lc->nsects + i] = NULL;
	i = 0;
	while (sections && sections[i])
	{
		tmp[i] = sections[i];
		i++;
	}
	sec = (struct section_64 *)(lc + 1);
	while (j < lc->nsects)
		tmp[i + j++] = (sec++)->sectname;
	free(sections);
	return (tmp);
}

int			ft_handle_64(void *ptr)
{
	int							ncmds;
	struct mach_header_64		*header;
	struct load_command			*lc;
	t_vars						vars;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = ptr + sizeof(*header);
	while (ncmds-- > 0)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			vars.sec = sec_64(vars.sec, (struct segment_command_64*)lc);
		}
		if (lc->cmd == LC_SYMTAB)
		{
			return (get_sym_64((struct symtab_command *)lc, ptr, vars));
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_FAILURE);
}
