/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antini <antini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 10:56:36 by antini            #+#    #+#             */
/*   Updated: 2019/08/19 12:24:26 by antini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			block_32(struct nlist list, char *t, t_vars vars, t_lst **lst)
{
	if (ft_create_block_32(lst, list, vars.sec, t))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	get_sym_32(struct symtab_command *sym, void *ptr, t_vars vars)
{
	uint32_t				i;
	char					*stringtable;
	struct nlist			*array;
	t_lst					*lst;

	i = 0;
	lst = NULL;
	array = ptr + sym->symoff;
	stringtable = ptr + sym->stroff;
	while (i < sym->nsyms)
	{
		if (!(array[i].n_type & N_STAB))
			if (block_32(array[i], stringtable, vars, &lst))
				return (EXIT_FAILURE);
		i++;
	}
	free(vars.sec);
	print_out(lst, 1);
	return (EXIT_SUCCESS);
}

static char	**sec_32(char **sections, struct segment_command *lc)
{
	struct section			*sec;
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
	sec = (struct section *)(lc + 1);
	while (j < lc->nsects)
		tmp[i + j++] = (sec++)->sectname;
	free(sections);
	return (tmp);
}

int			ft_handle_32(void *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;
	t_vars					vars;

	i = 0;
	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	lc = ptr + sizeof(*header);
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			vars.sec = sec_32(vars.sec, (struct segment_command *)lc);
		}
		if (lc->cmd == LC_SYMTAB)
		{
			return (get_sym_32((struct symtab_command *)lc, ptr, vars));
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_FAILURE);
}
