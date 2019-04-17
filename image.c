/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <cocummin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:50:21 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 13:50:45 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_point_to_image(t_texture *image, int x, int y, t_rgb rgb)
{
	int	index;

	index = 0;
	if (x < 0 || y < 0 || x > CW - 1 || y > CH - 1)
		return ;
	else
	{
		index = image->len * y * 4 + x * 4;
		image->image_data[index + 2] = rgb.r;
		image->image_data[index + 1] = rgb.g;
		image->image_data[index] = rgb.b;
	}
}
