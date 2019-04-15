#include "wolf3d.h"

t_rgb get_rgb_from_texture(int col, int row, t_texture *texture)
{
	int index;
	t_rgb rgb;
/*
	if (col < 0)
		col *= -1;
	if (row < 0)
		row *= -1;
	if (col > texture->len)
		col = texture->len - 1;
	if (row > texture->len)
		row = texture->len - 1;
*/

	index = texture->len * row * 4 + col * 4;

	rgb.r = texture->image_data[index + 2];
	rgb.g = texture->image_data[index + 1];
	rgb.b = texture->image_data[index];

	return(rgb);
}
