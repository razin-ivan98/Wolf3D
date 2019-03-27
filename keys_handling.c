#include "wolf3d.h"

int key_pressed(int key, t_wolf3d *wolf3d)
{
	//t_wolf3d *wolf3d;

	//wolf3d = (t_wolf3d *)param;

	pthread_t thread;


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
		if (get_tile(wolf3d->player.pos_x + 0.3*cos(wolf3d->player.angle), wolf3d->player.pos_y + 0.3*sin(wolf3d->player.angle), wolf3d) <= 0)
		{
			wolf3d->player.pos_x += 0.3*cos(wolf3d->player.angle);
			wolf3d->player.pos_y += 0.3*sin(wolf3d->player.angle);
			wolf3d->door = 0;
		}
		else if (get_tile(wolf3d->player.pos_x + 0.3*cos(wolf3d->player.angle), wolf3d->player.pos_y + 0.3*sin(wolf3d->player.angle), wolf3d) == 6)
			wolf3d->door = 1;
	}
	else if (key ==0x07D)
	{
		if (get_tile(wolf3d->player.pos_x - 0.3*cos(wolf3d->player.angle), wolf3d->player.pos_y - 0.3*sin(wolf3d->player.angle), wolf3d) <= 0)
		{
			wolf3d->player.pos_x -= 0.3*cos(wolf3d->player.angle);
			wolf3d->player.pos_y -= 0.3*sin(wolf3d->player.angle);
			wolf3d->door = 0;
		}
	}

	else if (key == 0x03)
	{
		if (wolf3d->door)
			wolf3d_init(wolf3d, "maps/simple");

	}


	provider(wolf3d);
}
