/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antini <antini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:08:16 by antini            #+#    #+#             */
/*   Updated: 2019/08/19 12:46:50 by antini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int			ft_display_32(struct section *sec, char *header)
{
	uint32_t					i;
	uint32_t					y;
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

static int	sec_32(struct segment_command *segment, char *header)
{
	struct section			*sec;

	sec = (struct section *)(segment + 1);
	while (segment->nsects-- > 0)
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
			return (ft_display_32(sec, header));
		sec++;
	}
	return (0);
}

int			ft_handle_32(void *ptr, int r)
{
	int						ncmds;
	struct mach_header		*header;
	struct segment_command	*seg_c;

	header = (struct mach_header *)ptr;
	seg_c = ptr + sizeof(*header);
	while (ncmds-- > 0)
	{
		if (ft_strcmp(seg_c->segname, SEG_TEXT) == 0)
			return (sec_32(seg_c, (char *)header));
		seg_c = (void *)seg_c + seg_c->cmdsize;
	}
	return (0);
}
