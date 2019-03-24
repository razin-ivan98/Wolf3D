#include "wolf3d.h"

t_rgb calculate_light(t_rgb rgb, float distance)
{
	t_rgb ret;

	ret.r = (rgb.r < 0 ? 255 + rgb.r : rgb.r) * (1 - 0.1 * distance);
	ret.g = (rgb.g < 0 ? 255 + rgb.g : rgb.g) * (1 - 0.1 * distance);
	ret.b = (rgb.b < 0 ? 255 + rgb.b : rgb.b) * (1 - 0.1 * distance);

	if (ret.r < 0)
		ret.r = 0;
	if (ret.g < 0)
		ret.g = 0;
	if (ret.b < 0)
		ret.b = 0;

	return (ret);
}

t_rgb color_to_rgb(int color)
{
	t_rgb rgb;

	rgb.r = color >> 16;
	rgb.g = (color & 0x00ff00) >> 8;
	rgb.b = color & 0x0000ff;

	return (rgb);
}

int rgb_to_color(t_rgb rgb)
{
	int color;

	color = rgb.r * 0x010000 + rgb.g * 0x000100 + rgb.b;

	return (color);
}