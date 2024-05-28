/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 01:29:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/05/29 03:39:04 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BITMAP_H
# define FT_BITMAP_H

# include <malloc.h>
# include <string.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>

/* Bitmap standard header sizes */

# define BITMAP_FILE_HEADER_SIZE 14
# define BITMAP_INFO_HEADER_SIZE 40
# define BITMAP_HEADER_SIZE 54

# define BI_RGB 0

/* Bitmap common parameters used for creating bitmaps. */

# define FT_BITMAP_BITS_PER_PIXEL 24
# define FT_BITMAP_BYTES_PER_PIXEL 3
# define FT_BITMAP_PLANES 1
# define FT_BITMAP_COMPRESSION 0
# define FT_BITMAP_X_PIXELS_PER_METER 2835
# define FT_BITMAP_Y_PIXELS_PER_METER 2835

typedef struct s_bfheader	t_bfheader;
typedef struct s_biheader	t_biheader;
typedef struct s_ftbitmap	t_ftbitmap;

struct s_bfheader
{
	uint8_t		bf_type[2];
	uint32_t	bf_size;
	uint16_t	bf_reserved1;
	uint16_t	bf_reserved2;
	uint32_t	bf_off_bits;
};

struct s_biheader
{
	uint32_t	bi_size;
	int32_t		bi_width;
	int32_t		bi_height;
	uint16_t	bi_planes;
	uint16_t	bi_bit_count;
	uint32_t	bi_compression;
	uint32_t	bi_size_image;
	int32_t		bi_x_pels_per_meter;
	int32_t		bi_y_pels_per_meter;
	uint32_t	bi_clr_used;
	uint32_t	bi_clr_important;
};

struct s_ftbitmap
{
	t_bfheader			fh;
	t_biheader			ih;
	unsigned char		*data;
};

t_ftbitmap	*ft_load_bitmap(const char *filename);
t_ftbitmap	*ft_create_bitmap(const char *filename, \
	uint32_t width, uint32_t height);

void		ft_save_bitmap(const char *filename, t_ftbitmap *bitmap);

static inline uint32_t	ft_bitmap_get_stride(t_ftbitmap *bitmap)
{
	return ((((bitmap->ih.biWidth * bitmap->ih.biBitCount) + 31) & ~31) >> 3);
}

static inline unsigned char	*ft_bitmap_get_pixel(t_ftbitmap *bitmap, \
	uint32_t x, uint32_t y)
{
	return (bitmap->data + (y * ft_bitmap_get_stride(bitmap) + \
		x * FT_BITMAP_BYTES_PER_PIXEL));
}

#endif
