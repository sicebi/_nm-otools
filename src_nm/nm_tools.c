/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antini <antini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 10:57:06 by antini            #+#    #+#             */
/*   Updated: 2019/08/19 12:10:30 by antini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		free_lst(t_lst **lst)
{
	t_lst	*tmp;

	tmp = NULL;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->value)
			free((*lst)->value);
		(*lst)->next = NULL;
		free(*lst);
		(*lst) = tmp;
	}
}

char		ft_type(uint8_t type, uintmax_t value, uint8_t sect,
	char **sections)
{
	char	*section_name;
	char	ret;

	ret = 0;
	ret = ((type & N_TYPE) == N_INDR) ? 'I' : ret;
	ret = (!ret && (type & N_TYPE) == N_STAB) ? '-' : ret;
	ret = (!ret && (type & N_TYPE) == N_UNDF
		&& (ret & N_EXT) && value != 0) ? 'C' : ret;
	ret = (!ret && (type & N_TYPE) == N_UNDF
		&& (type & N_TYPE) == N_PBUD) ? 'u' : ret;
	ret = (!ret && (type & N_TYPE) == N_UNDF) ? 'U' : ret;
	ret = (!ret && (type & N_TYPE) == N_ABS) ? 'A' : ret;
	if (!ret && (type & N_TYPE) == N_SECT)
	{
		section_name = sections[sect - 1];
		ret = (section_name && (!ft_strcmp(section_name, "__text")
			|| !ft_strcmp(section_name, "__data")
			|| !ft_strcmp(section_name, "__bss"))) ?
		ft_toupper(section_name[2]) : 'S';
	}
	if (!ret)
		return (' ');
	return (!(type & N_EXT) ? ft_tolower(ret) : ret);
}

char		*ft_add_precision(uintmax_t value, int is64bit)
{
	char	*str;
	char	*res;
	int		system_type;
	int		i;
	int		len;

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
	return (res);
}

void		print_out(t_lst *lst, int is64bit)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->value == NULL)
			if (is64bit == 1)
				ft_putstr("                ");
			else
				ft_putstr("        ");
		else
			ft_putstr(tmp->value);
		ft_putchar(' ');
		ft_putchar(tmp->type);
		ft_putchar(' ');
		ft_putstr(tmp->name);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	free_lst(&lst);
}
