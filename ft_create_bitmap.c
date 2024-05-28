/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bitmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 02:28:19 by kdaniely          #+#    #+#             */
/*   Updated: 2024/05/29 03:39:46 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmap.h"

static void	fill_file_header(t_ftbitmap *bitmap);
static void	fill_info_header(t_ftbitmap *bitmap, \
	uint32_t width, uint32_t height);

t_ftbitmap	*ft_create_bitmap(const char *filename, \
	uint32_t width, uint32_t height)
{
	t_ftbitmap	*bitmap;
	int			fd;

	fd = open(filename, O_WRONLY | O_CREAT, O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	bitmap = (t_ftbitmap *)malloc(sizeof(t_ftbitmap));
	if (!bitmap)
	{
		close(fd);
		return (NULL);
	}
	fill_file_header(bitmap);
	fill_info_header(bitmap, width, height);
	bitmap->data = (unsigned char *)malloc(bitmap->ih.biSizeImage);
	if (!bitmap->data)
	{
		free(bitmap);
		close(fd);
		return (NULL);
	}
	memset(bitmap->data, 255, bitmap->ih.biSizeImage);
	return (bitmap);
}

static void	fill_file_header(t_ftbitmap *bitmap)
{
	bitmap->fh.bfType = {'B', 'M'};
	bitmap->fh.bfSize = BITMAP_HEADER_SIZE + width * height * 3;
	bitmap->fh.bfReserved1 &= 0;
	bitmap->fh.bfReserved2 &= 0;
	bitmap->fh.bfOffBits = BITMAP_HEADER_SIZE;
}

/* stride = ((((biWidth * biBitCount) + 31) & ~31) >> 3); */

static void	fill_info_header(t_ftbitmap *bitmap, \
	uint32_t width, uint32_t height)
{
	bitmap->ih.biSize = BITMAP_INFO_HEADER_SIZE;
	bitmap->ih.biWidth = width;
	bitmap->ih.biHeight = -height;
	bitmap->ih.biPlanes = FT_BITMAP_PLANES;
	bitmap->ih.biBitCount = FT_BITMAP_BITS_PER_PIXEL;
	bitmap->ih.biCompression = BI_RGB;
	bitmap->ih.biSizeImage = (-height) * ft_bitmap_get_stride(bitmap);
	bitmap->ih.biXPelsPerMeter = FT_BITMAP_X_PIXELS_PER_METER;
	bitmap->ih.biYPelsPerMeter = FT_BITMAP_Y_PIXELS_PER_METER;
	bitmap->ih.biClrUsed = 0;
	bitmap->ih.biClrImportant = 0;
}
