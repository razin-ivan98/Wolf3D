/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <cocummin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:45:49 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 13:48:30 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_rgb	calculate_light(t_rgb rgb, float distance)
{
	t_rgb	ret;
	float	delta;

	delta = 1 - 0.1 * distance;
	ret.r = (rgb.r < 0 ? 255 + rgb.r : rgb.r) * delta;
	ret.g = (rgb.g < 0 ? 255 + rgb.g : rgb.g) * delta;
	ret.b = (rgb.b < 0 ? 255 + rgb.b : rgb.b) * delta;
	if (ret.r < 0)
		ret.r = 0;
	if (ret.g < 0)
		ret.g = 0;
	if (ret.b < 0)
		ret.b = 0;
	return (ret);
}

t_rgb	color_to_rgb(int color)
{
	t_rgb rgb;

	rgb.r = color >> 16;
	rgb.g = (color & 0x00ff00) >> 8;
	rgb.b = color & 0x0000ff;
	return (rgb);
}

int		rgb_to_color(t_rgb rgb)
{
	int color;

	color = rgb.r * 0x010000 + rgb.g * 0x000100 + rgb.b;
	return (color);
}
