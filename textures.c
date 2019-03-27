#include "wolf3d.h"

t_rgb get_rgb_from_texture(int col, int row, t_texture *texture)
{
	int index;
	t_rgb rgb;

	index = texture->len * row * 4 + col * 4;

	rgb.r = texture->image_data[index + 2];
	rgb.g = texture->image_data[index + 1];
	rgb.b = texture->image_data[index];

	return(rgb);
}
