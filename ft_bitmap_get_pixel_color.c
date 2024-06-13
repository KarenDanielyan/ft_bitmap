/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmap_get_pixel_color.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:34:15 by kdaniely          #+#    #+#             */
/*   Updated: 2024/06/13 21:44:20 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmap.h"

uint32_t	get_byte_color(uint32_t rgb, uint32_t channel_mask)
{
	int			count;
	uint32_t	tmp;

	tmp = channel_mask;
	count = 0;
	while (tmp != 0xFF)
	{
		tmp = tmp >> 1;
		count ++;
	}
	return ((channel_mask & rgb) >> count);
}

// ARGB format;
uint32_t	ft_bitmap_get_pixel_color(t_ftbitmap *bitmap, \
	uint32_t x, uint32_t y)
{
	uint32_t	*pixel;
	uint32_t	color;

	color = 0;
	pixel = (uint32_t *)ft_bitmap_get_pixel(bitmap, x, y);
	if (pixel && bitmap->fh.bf_off_bits == BITMAP_V5HEADER_SIZE)
	{
		color = bitmap->v5ih.bi_blue_mask & *pixel;
		color |= get_byte_color(*pixel, bitmap->v5ih.bi_green_mask) << 8;
		color |= get_byte_color(*pixel, bitmap->v5ih.bi_red_mask) << 16;
		if (bitmap->ih.bi_bit_count == 32)
			color |= get_byte_color(*pixel, bitmap->v5ih.bi_alpha_mask) << 24;
	}
	else if (pixel)
		color = *pixel;
	if (bitmap->ih.bi_bit_count != 32)
		color &= 0x00FFFFFF;
	return (color);
}
