/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmap_properties.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:37:57 by kdaniely          #+#    #+#             */
/*   Updated: 2024/06/12 18:34:59 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmap.h"

void	ft_bitmap_set_pixel(t_ftbitmap *bitmap, uint32_t x, uint32_t y, \
	unsigned int color)
{
	unsigned char	*pixel;

	if (!bitmap)
		return ;
	pixel = ft_bitmap_get_pixel(bitmap, x, y);
	if (bitmap->ih.bi_bit_count == 32)
		*(pixel + 3) = color & 0xFF000000;
	*pixel = color & 0x000000FF;
	*(pixel + 1) = (color & 0x0000FF00) >> 8;
	*(pixel + 2) = (color & 0x00FF0000) >> 16;
}

unsigned char	*ft_bitmap_get_pixel(t_ftbitmap *bitmap, int32_t x, int32_t y)
{
	unsigned char	*pixel;
	int32_t			width;
	int32_t			height;

	pixel = NULL;
	if (bitmap)
	{
		width = abs(bitmap->ih.bi_width);
		height = abs(bitmap->ih.bi_height);
		if (x < width && x > -width && y < height && y > -height)
		{
			if (x < 0)
				x = width + x;
			if (y < 0)
				y = height + y;
			pixel = bitmap->data + (y * ft_bitmap_get_stride(bitmap) + \
			x * (bitmap->ih.bi_bit_count / 8));
		}
	}
	return (pixel);
}
