/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 01:29:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/05/29 21:38:53 by kdaniely         ###   ########.fr       */
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

typedef struct s_ftbitmap	t_ftbitmap;

typedef struct s_bfheader	t_bfheader;
typedef struct s_biheader	t_biheader;
typedef struct s_biv5header	t_biv5header;

struct s_bfheader
{
	uint8_t		bf_type[2];
	uint32_t	bf_size;
	uint16_t	bf_reserved1;
	uint16_t	bf_reserved2;
	uint32_t	bf_off_bits;
} __attribute__((packed));

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
} __attribute__((packed));

/*
  DWORD        bV5CSType;
  CIEXYZTRIPLE bV5Endpoints;
  DWORD        bV5GammaRed;
  DWORD        bV5GammaGreen;
  DWORD        bV5GammaBlue;
  DWORD        bV5Intent;
  DWORD        bV5ProfileData;
  DWORD        bV5ProfileSize;
  DWORD        bV5Reserved;
*/

struct s_biv5header
{
	uint32_t	bi_red_mask;
	uint32_t	bi_green_mask;
	uint32_t	bi_blue_mask;
	uint32_t	bi_alpha_mask;
	uint32_t	bi_cst_type;
	uint32_t	bi_endpoints[9];
	uint32_t	bi_gamma_red;
	uint32_t	bi_gamma_green;
	uint32_t	bi_gamma_blue;
	uint32_t	bi_intent;
	uint32_t	bi_profile_data;
	uint32_t	bi_profile_size;
	uint32_t	bi_reserved;
} __attribute__((packed));

struct s_ftbitmap
{
	t_bfheader			fh;
	t_biheader			ih;
	t_biv5header		v5ih;
	unsigned char		*data;
} __attribute__((packed));

t_ftbitmap	*ft_load_bitmap(const char *filename);

t_ftbitmap	*ft_create_bitmap(uint32_t width, uint32_t height);

int			ft_save_bitmap(t_ftbitmap *bitmap, const char *filename);

void		ft_destroy_bitmap(t_ftbitmap *bitmap);

static inline uint32_t	ft_bitmap_get_stride(t_ftbitmap *bitmap)
{
	return (\
		(((bitmap->ih.bi_width * bitmap->ih.bi_bit_count) + 31) & ~31) >> 3);
}

static inline unsigned char	*ft_bitmap_get_pixel(t_ftbitmap *bitmap, \
	uint32_t x, uint32_t y)
{
	return (bitmap->data + (y * ft_bitmap_get_stride(bitmap) + \
		x * (bitmap->ih.bi_bit_count / sizeof(char))));
}

#endif
