/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antini <antini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:07:26 by antini            #+#    #+#             */
/*   Updated: 2019/08/19 12:46:27 by antini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int			ft_display_64(struct section_64 *sec, char *header)
{
	uint64_t					i;
	uint64_t					y;
	uintmax_t					x;

	i = 0;
	x = 1;
	while (i < sec->size)
	{
		ft_add_precision((uintmax_t)sec->addr, 1);
		ft_putchar('	');
		y = -1;
		while (++y < 16 && y + i < sec->size)
		{
			print_byte_to_hex(*(sec->offset + header + y + i), x);
			x++;
		}
		ft_putchar('\n');
		sec->addr = sec->addr + 16;
		i += 16;
	}
	return (0);
}

static int	sec_64(struct segment_command_64 *segment, char *header)
{
	struct section_64			*sec;

	sec = (struct section_64 *)(segment + 1);
	while (segment->nsects-- > 0)
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
			return (ft_display_64(sec, header));
		sec++;
	}
	return (0);
}

int			ft_handle_64(void *ptr, int r)
{
	int							ncmds;
	struct mach_header_64		*header;
	struct segment_command_64	*seg_c;

	header = (struct mach_header_64 *)ptr;
	seg_c = ptr + sizeof(*header);
	while (ncmds-- > 0)
	{
		if (ft_strcmp(seg_c->segname, SEG_TEXT) == 0)
			return (sec_64(seg_c, (char *)header));
		seg_c = (void *)seg_c + seg_c->cmdsize;
	}
	return (0);
}
