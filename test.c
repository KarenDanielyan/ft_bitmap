/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:42:49 by kdaniely          #+#    #+#             */
/*   Updated: 2024/05/31 02:35:43 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_bitmap.h"

int	main(void)
{
	t_ftbitmap	*bitmap;

	printf("Loading bitmap...\n");
	bitmap = ft_load_bitmap("example.bmp");
	ft_save_bitmap(bitmap, "result.bmp");
	ft_save_bitmap(bitmap, "result.hex");
	printf("Done.\n");
	ft_destroy_bitmap(bitmap);
	return (0);
}
