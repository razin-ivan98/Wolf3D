#include "wolf3d.h"

int get_tile(float x, float y, t_wolf3d *wolf3d)
{
	return (wolf3d->map[(int)(x)][(int)(y)]);
}