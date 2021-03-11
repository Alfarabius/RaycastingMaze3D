/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:05:47 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/10 17:46:05 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	void	img_to_bmp(t_all *all, int h, int w, int fd)
{
	int		i;
	int		j;
	int		pxl;
	int		err;
	void	*adr;

	i = 1;
	err = 0;
	adr = all->prg.addr;
	while (i <= h)
	{
		j = 0;
		pxl = w * (h - i);
		while (j++ < w)
			err |= write(fd, &adr[pxl++ * all->prg.bits_per_pixel / 8], 4);
		i++;
	}
	err == -1 ? error_handler("error while write img to bmp file") : 0;
}

static	void	add_header(int size, int h, int w, int fd)
{
	t_bmp	bmp;
	int		err;
	int		i;

	i = 0;
	err = 0;
	bmp.bpp = 32;
	bmp.rsv = 0;
	bmp.off = 54;
	bmp.hdr = 40;
	bmp.pln = 1;
	err |= write(fd, "BM", 2);
	err |= write(fd, &size, 4);
	err |= write(fd, &bmp.rsv, 4);
	err |= write(fd, &bmp.off, 4);
	err |= write(fd, &bmp.hdr, 4);
	err |= write(fd, &w, 4);
	err |= write(fd, &h, 4);
	err |= write(fd, &bmp.pln, 2);
	err |= write(fd, &bmp.bpp, 2);
	while (i++ < 6)
		err |= write(fd, &bmp.rsv, 4);
	err == -1 ? error_handler("error while write to bmp file") : 0;
}

int				make_screenshot(int h, int w, t_all *all)
{
	int	size;
	int	fd;

	fd = open("screenshot.bmp", O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		return (error_handler("fd of screenshot.bmp return -1"));
	size = 54 + h * w * 4;
	add_header(size, h, w, fd);
	img_to_bmp(all, h, w, fd);
	close(fd);
	exit(0);
	return (1);
}
