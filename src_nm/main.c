/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antini <antini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 10:55:10 by antini            #+#    #+#             */
/*   Updated: 2019/08/19 12:27:55 by antini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		ft_nm(void *ptr)
{
	uint32_t				magic_number;

	magic_number = 0;
	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC_64)
		return (ft_handle_64(ptr));
	if (magic_number == MH_MAGIC)
		return (ft_handle_32(ptr));
	return (0);
}

int		main(int ac, char **av)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if (ac != 2)
		fprintf(stderr, "please give me a  arg\n");
	if ((fd = open(av[1], O_RDONLY)) < 0)
		perror("error");
	if (fstat(fd, &buf) < 0)
		perror("fstat");
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	ft_nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
