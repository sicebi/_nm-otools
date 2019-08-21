/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_uimax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antini <antini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 12:50:03 by antini            #+#    #+#             */
/*   Updated: 2019/08/19 11:36:02 by antini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_nbrlen_uimax(uintmax_t n, size_t base)
{
	size_t			i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

char				*ft_itoa_base_uimax(uintmax_t n, size_t base)
{
	char			*str;
	size_t			len;

	len = ft_nbrlen_uimax(n, base);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[--len] = '0';
	else
	{
		while (n != 0)
		{
			if (base > 10 && n % base > 9)
				str[--len] = (n % base) + ('a' - 10);
			else
				str[--len] = (n % base) + 48;
			n = n / base;
		}
	}
	return (str);
}
