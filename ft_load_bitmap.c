/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_bitmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 02:04:46 by kdaniely          #+#    #+#             */
/*   Updated: 2024/05/29 21:28:24 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmap.h"

static void	load_header(t_ftbitmap *bitmap, int fd);

t_ftbitmap	*ft_load_bitmap(const char *filename)
{
	t_ftbitmap	*bitmap;
	size_t		buffersize;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	bitmap = (t_ftbitmap *)malloc(sizeof(t_ftbitmap));
	if (!bitmap)
	{
		close(fd);
		return (NULL);
	}
	load_header(bitmap, fd);
	buffersize = bitmap->fh.bf_size - bitmap->fh.bf_off_bits;
	bitmap->data = (unsigned char *)malloc(buffersize);
	if (!bitmap->data)
	{
		free(bitmap);
		close(fd);
		return (NULL);
	}
	read(fd, bitmap->data, buffersize);
	close(fd);
	return (bitmap);
}

static void	load_header(t_ftbitmap *bitmap, int fd)
{
	read(fd, &bitmap->fh, sizeof(struct s_bfheader));
	read(fd, &bitmap->ih, sizeof(struct s_biheader));
	if (bitmap->ih.bi_size == sizeof(t_biheader) + sizeof(t_biv5header))
		read(fd, &bitmap->v5ih, sizeof(t_biv5header));
}
