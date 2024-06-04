/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:42:49 by kdaniely          #+#    #+#             */
/*   Updated: 2024/06/04 18:20:22 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_bitmap.h"

int	main(void)
{
	t_ftbitmap	*bitmap;

	printf("Loading bitmap...\n");
	bitmap = ft_load_bitmap("example.bmp");
	printf("Done.\n");
	printf("Color of the first pixel is: %x.\n", \
	ft_bitmap_get_pixel_color(bitmap, 0, 0));
	ft_save_bitmap(bitmap, "result.bmp");
	ft_save_bitmap(bitmap, "result.hex");
	ft_destroy_bitmap(bitmap);
	return (0);
}
