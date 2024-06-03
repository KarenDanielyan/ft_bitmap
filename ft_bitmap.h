/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 01:29:12 by kdaniely          #+#    #+#             */
/*   Updated: 2024/06/03 15:02:25 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BITMAP_H
# define FT_BITMAP_H

# include <stdlib.h>
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

/**
 * @brief	The BITMAPFILEHEADER structure.
 * 
 */
struct s_bfheader
{
	uint8_t		bf_type[2];
	uint32_t	bf_size;
	uint16_t	bf_reserved1;
	uint16_t	bf_reserved2;
	uint32_t	bf_off_bits;
} __attribute__((packed));

/**
 * @brief	The BITMAPINFOHEADER structure.
 * 			Refer to the Microsoft documentation for more information.
 * 
 */
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

/**
 * @brief	The BITMAPV5HEADER structure.
 * 			It only contains the fields that are missing in BITMAPINFOHEADER.
 * 			Refer to the Microsoft documentation for more information.
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

/**
 * @brief	This is the bitmap structure for ft_bitmap API.
 * 			It contains the bitmap file header, info header, 
 * 			and the bitmap data.
 * 			We support both BITMAPINFOHEADER and BITMAPV5HEADER,
 * 			but in @ref t_biv5header, are only the fields 
 * 			that are missing in @ref t_biheader.
 * 			Note that this structure is packed to avoid padding.
 * 
 */
struct s_ftbitmap
{
	t_bfheader			fh;
	t_biheader			ih;
	t_biv5header		v5ih;
	unsigned char		*data;
} __attribute__((packed));

/**
 * @brief	ft_load_bitmap() loads v3 or v5 bitmap into memory.
 * 
 * @param filename		The path to the bitmap file.
 * @return t_ftbitmap*	Returns a pointer to the ft_bitmap structure.
 */
t_ftbitmap	*ft_load_bitmap(const char *filename);

/**
 * @brief				ft_create_bitmap() creates a new v3 bitmap structure.
 * 						It fills the data field with white pixels.
 * 
 * @param width			Width of the bitmap.
 * @param height		Height of the bitmap.
 * @return t_ftbitmap*	Returns a pointer to the ft_bitmap structure.
 */
t_ftbitmap	*ft_create_bitmap(uint32_t width, uint32_t height);

/**
 * @brief				ft_create_bitmap_from_data() creates a bitmap using
 * 						the provided pixel data.
 * 							- The data must be in BGRA format.
 * 							- The data does not contain padding.
 */
t_ftbitmap	*ft_create_bitmap_from_data(uint32_t width, uint32_t height, \
	unsigned char *data);

/**
 * @brief			ft_save_bitmap() saves the bitmap structure to a file.
 * 
 * @param bitmap	Pointer to the ft_bitmap structure to be saved.
 * @param filename	The path to the file where the bitmap will be saved.
 * @return int		Returns 0 if the bitmap was saved successfully, otherwise -1.
 */
int			ft_save_bitmap(t_ftbitmap *bitmap, const char *filename);

/**
 * @brief			ft_destroy_bitmap() frees the memory 
 * 					allocated for the bitmap.
 * 
 * @param bitmap	Pointer to the ft_bitmap structure to be freed.
 */
void		ft_destroy_bitmap(t_ftbitmap *bitmap);

/**
 * @brief		ft_bitmap_set_pixel() sets the pixel at (x, y) to the color.
 * 					- The color must be in ARGB format (little endian) or 
 * 					BGRA (big endian).
 * 					- The bitmap must be 24 or 32 bits per pixel.
 * 					- In case of 24 bits per pixel, the alpha channel is ignored.
 */
void		ft_bitmap_set_pixel(t_ftbitmap *bitmap, uint32_t x, uint32_t y, \
	unsigned int color);

/**
 * @brief			ft_bitmap_get_stride() calculates the stride of the bitmap.
 * 					The stride is the number of bytes in a row of the bitmap,
 * 					including padding.
 * 
 * @param bitmap	Pointer to the ft_bitmap structure.
 * @return uint32_t	Returns the stride of the bitmap.
 */
static inline uint32_t	ft_bitmap_get_stride(t_ftbitmap *bitmap)
{
	return (\
		(((bitmap->ih.bi_width * bitmap->ih.bi_bit_count) + 31) & ~31) >> 3);
}

/**
 * @brief		ft_bitmap_get_pixel() returns a pointer to the pixel at (x, y).
 * 
 */
static inline unsigned char	*ft_bitmap_get_pixel(t_ftbitmap *bitmap, \
	uint32_t x, uint32_t y)
{
	return (bitmap->data + (y * ft_bitmap_get_stride(bitmap) + \
		x * (bitmap->ih.bi_bit_count / 8)));
}

#endif
