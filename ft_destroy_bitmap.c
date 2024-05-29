/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_bitmap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:38:13 by kdaniely          #+#    #+#             */
/*   Updated: 2024/05/29 21:49:17 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitmap.h"

void	ft_destroy_bitmap(t_ftbitmap *bitmap)
{
	free(bitmap->data);
	free(bitmap);
}
