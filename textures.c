#include "wolf3d.h"

t_rgb get_rgb_from_texture(int col, int row, char *image_data)
{
	int index;
	t_rgb rgb;

	index = TEX_SIZE * row * 4 + col * 4;

	rgb.r = image_data[index + 2];
	rgb.g = image_data[index + 1];
	rgb.b = image_data[index];

	return(rgb);
}
