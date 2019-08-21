/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antini <antini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:27:13 by antini            #+#    #+#             */
/*   Updated: 2019/08/19 13:06:49 by antini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void				ft_add_precision(uintmax_t value, int is64bit)
{
	char			*str;
	char			*res;
	int				system_type;
	int				i;
	int				len;

	i = 0;
	str = ft_itoa_base_uimax(value, 16);
	len = ft_strlen(str);
	system_type = is64bit == 1 ? 16 : 8;
	res = (char *)malloc(sizeof(char) * (system_type + 1));
	res[system_type] = '\0';
	while (i < system_type - len)
		res[i++] = '0';
	while (i < system_type)
	{
		res[i] = str[i - (system_type - len)];
		i++;
	}
	free(str);
	ft_putstr(res);
	free(res);
}

void				print_byte_to_hex(char byte, uintmax_t x)
{
	char			str[2];
	short			char_hex;
	unsigned char	cast;
	t_vars			v;

	cast = (unsigned char)byte;
	v.count = -1;
	while (++v.count != 2)
	{
		char_hex = cast % 16;
		cast /= 16;
		if (char_hex < 10)
			str[v.count] = char_hex + '0';
		else
			str[v.count] = (char_hex % 10) + 'a';
	}
	ft_putchar(str[1]);
	ft_putchar(str[0]);
	if (v.env > 3)
	{
		if (x % 4 == 0)
			ft_putchar(' ');
	}
	else
		ft_putchar(' ');
}
