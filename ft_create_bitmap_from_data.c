/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bitmap_from_data.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 02:28:19 by kdaniely          #+#    #+#             */
/*   Updated: 2024/05/31 02:36:06 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmap.h"

static void	fill_file_header(t_ftbitmap *bitmap, \
	uint32_t width, uint32_t height)
{
	bitmap->fh.bf_type[0] = 'B';
	bitmap->fh.bf_type[1] = 'M';
	bitmap->fh.bf_size = BITMAP_HEADER_SIZE + (height * width);
	bitmap->fh.bf_reserved1 &= 0;
	bitmap->fh.bf_reserved2 &= 0;
	bitmap->fh.bf_off_bits = BITMAP_HEADER_SIZE;
}

static void	fill_info_header(t_ftbitmap *bitmap, \
	uint32_t width, uint32_t height)
{
	bitmap->ih.bi_size = BITMAP_INFO_HEADER_SIZE;
	bitmap->ih.bi_width = width;
	bitmap->ih.bi_height = -height;
	bitmap->ih.bi_planes = FT_BITMAP_PLANES;
	bitmap->ih.bi_bit_count = FT_BITMAP_BITS_PER_PIXEL;
	bitmap->ih.bi_compression = BI_RGB;
	bitmap->ih.bi_size_image = height * ft_bitmap_get_stride(bitmap);
	bitmap->ih.bi_x_pels_per_meter = FT_BITMAP_X_PIXELS_PER_METER;
	bitmap->ih.bi_y_pels_per_meter = FT_BITMAP_Y_PIXELS_PER_METER;
	bitmap->ih.bi_clr_used = 0;
	bitmap->ih.bi_clr_important = 0;
}

/* Fill bitmap data with pixel information. Consider padding too.*/
/* BGRA -> RGB */
/*
 * Little Endian: 00 00 FF 00 <- 00FF0000
*/
static void	fill_data(t_ftbitmap *bitmap, unsigned char *data)
{
	int32_t			i;
	int32_t			j;
	int32_t			height;
	unsigned int	color;

	i = 0;
	height = bitmap->ih.bi_height;
	if (height < 0)
		height = -height;
	while (i < height)
	{
		j = 0;
		while (j < bitmap->ih.bi_width)
		{
			color = \
			*((unsigned int *)(data + (i * bitmap->ih.bi_width + j) * 4));
			ft_bitmap_set_pixel(bitmap, j, i, color);
			j ++;
		}
		i ++;
	}
}

/* Read pixel information from data. pixels in data are BGRA. */
t_ftbitmap	*ft_create_bitmap_from_data(uint32_t width, uint32_t height, \
	unsigned char *data)
{
	t_ftbitmap	*bitmap;

	bitmap = (t_ftbitmap *)malloc(sizeof(t_ftbitmap));
	if (!bitmap)
		return (NULL);
	fill_file_header(bitmap, width, height);
	fill_info_header(bitmap, width, height);
	bitmap->fh.bf_size = BITMAP_HEADER_SIZE + bitmap->ih.bi_size_image;
	bitmap->data = (unsigned char *)malloc(bitmap->ih.bi_size_image);
	if (!bitmap->data)
	{
		free(bitmap);
		return (NULL);
	}
	memset(bitmap->data, 0, bitmap->ih.bi_size_image);
	fill_data(bitmap, data);
	return (bitmap);
}
