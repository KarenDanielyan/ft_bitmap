/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bitmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 02:28:19 by kdaniely          #+#    #+#             */
/*   Updated: 2024/05/30 14:53:24 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmap.h"

static void	fill_file_header(t_ftbitmap *bitmap, \
	uint32_t width, uint32_t height);
static void	fill_info_header(t_ftbitmap *bitmap, \
	uint32_t width, uint32_t height);

t_ftbitmap	*ft_create_bitmap(uint32_t width, uint32_t height)
{
	t_ftbitmap	*bitmap;

	bitmap = (t_ftbitmap *)malloc(sizeof(t_ftbitmap));
	if (!bitmap)
		return (NULL);
	fill_file_header(bitmap, width, height);
	fill_info_header(bitmap, width, height);
	bitmap->data = (unsigned char *)malloc(bitmap->ih.bi_size_image);
	if (!bitmap->data)
	{
		free(bitmap);
		return (NULL);
	}
	memset(bitmap->data, 255, bitmap->ih.bi_size_image);
	return (bitmap);
}

t_ftbitmap	*ft_create_bitmap_from_data(uint32_t width, uint32_t height, \
	unsigned char *data)
{
	t_ftbitmap	*bitmap;
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	bitmap = (t_ftbitmap *)malloc(sizeof(t_ftbitmap));
	if (!bitmap)
		return (NULL);
	fill_file_header(bitmap, width, height);
	fill_info_header(bitmap, width, height);
	while (i < height * FT_BITMAP_BYTES_PER_PIXEL)
	{
		j = 0;
		while (j < width * FT_BITMAP_BYTES_PER_PIXEL)
		{
			*ft_bitmap_get_pixel(bitmap, j, i) = *(data + i * width + j);
			j ++;
		}
	}
	return (bitmap);
}

static void	fill_file_header(t_ftbitmap *bitmap, \
	uint32_t width, uint32_t height)
{
	bitmap->fh.bf_type[0] = 'B';
	bitmap->fh.bf_type[1] = 'M';
	bitmap->fh.bf_size = BITMAP_HEADER_SIZE + width * height * 3;
	bitmap->fh.bf_reserved1 &= 0;
	bitmap->fh.bf_reserved2 &= 0;
	bitmap->fh.bf_off_bits = BITMAP_HEADER_SIZE;
}

/* stride = ((((biWidth * biBitCount) + 31) & ~31) >> 3); */

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
