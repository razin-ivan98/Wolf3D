#include "wolf3d.h"

int get_tile(float x, float y, t_wolf3d *wolf3d)
{
	if (x < 0.0)
		x = 0.0;
	if (y < 0.0)
		y = 0.0;
	if (x >= (double)wolf3d->cols)
		x = (double)wolf3d->cols - 0.5;
	if (y >= (double)wolf3d->rows)
		y = (double)wolf3d->rows - 0.5;
	return (wolf3d->map[(int)(x)][(int)(y)]);
}
