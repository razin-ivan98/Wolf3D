#include "wolf3d.h"

void	put_point_to_image(char *image_data, int x, int y, int color)
{
	int	index = 0;

	if (x < 0 || y < 0 || x > CW - 1 || y > CH - 1)
		return ;
	else
	{
		index = CW * y * 4 + x * 4;
		image_data[index + 2] = color >> 16;
		image_data[index + 1] = (color & 0x00ff00) >> 8;
		image_data[index] = color & 0x0000ff;
	}
}