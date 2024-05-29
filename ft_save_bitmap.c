/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_bitmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:14:40 by kdaniely          #+#    #+#             */
/*   Updated: 2024/05/29 21:25:55 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmap.h"

int	ft_save_bitmap(t_ftbitmap *bitmap, const char *filename)
{
	int		fd;
	size_t	buffersize;

	fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (1);
	write(fd, &bitmap->fh, sizeof(t_bfheader));
	write(fd, &bitmap->ih, sizeof(t_biheader));
	if (bitmap->ih.bi_size == sizeof(t_biheader) + sizeof(t_biv5header))
		write(fd, &bitmap->v5ih, sizeof(t_biv5header));
	buffersize = bitmap->fh.bf_size - bitmap->fh.bf_off_bits;
	write(fd, bitmap->data, buffersize);
	close(fd);
	return (0);
}
