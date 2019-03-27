#include "wolf3d.h"

int key_pressed(int key, t_wolf3d *wolf3d)
{
	//t_wolf3d *wolf3d;

	//wolf3d = (t_wolf3d *)param;

	if (key == 0x35)
	{
		exit(1);
	}

	else if (key == 0x07C)
	{
		wolf3d->player.angle += M_PI/48;
	}
	else if (key ==0x07B)
	{
		wolf3d->player.angle -= M_PI/48;
	}
	else if (key ==0x07E)
	{
		if (get_tile(wolf3d->player.pos_x + cos(wolf3d->player.angle), wolf3d->player.pos_y + sin(wolf3d->player.angle), wolf3d) <= 0)
		{
			wolf3d->player.pos_x += 0.3*cos(wolf3d->player.angle);
			wolf3d->player.pos_y += 0.3*sin(wolf3d->player.angle);
		}
	}
	else if (key ==0x07D)
	{
		if (get_tile(wolf3d->player.pos_x - cos(wolf3d->player.angle), wolf3d->player.pos_y - sin(wolf3d->player.angle), wolf3d) <= 0)
		{
			wolf3d->player.pos_x -= 0.3*cos(wolf3d->player.angle);
			wolf3d->player.pos_y -= 0.3*sin(wolf3d->player.angle);
		}
	}
	provider(wolf3d);
}
