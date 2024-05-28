/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_bitmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 02:04:46 by kdaniely          #+#    #+#             */
/*   Updated: 2024/05/29 03:22:57 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmap.h"

t_ftbitmap	*ft_load_bitmap(const char *filename)
{
	t_ftbitmap	*bitmap;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	bitmap = (t_ftbitmap *)malloc(sizeof(t_ftbitmap));
	if (!bitmap)
		return (NULL);
	read(fd, &bitmap->fh, sizeof(struct s_bfheader));
	read(fd, &bitmap->ih, sizeof(struct s_biheader));
	bitmap->data = (unsigned char *)malloc(bitmap->ih.biSizeImage);
	if (!bitmap->data)
	{
		free(bitmap);
		return (NULL);
	}
	read(fd, bitmap->data, bitmap->ih.biSizeImage);
	close(fd);
	return (bitmap);
}
