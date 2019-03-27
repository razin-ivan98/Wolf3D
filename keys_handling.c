#include "wolf3d.h"

int key_pressed(int key, t_wolf3d *wolf3d)
{
	//t_wolf3d *wolf3d;

	//wolf3d = (t_wolf3d *)param;

	pthread_t thread;


	if (key == /*0x35*/0xff1b)
	{
		exit(1);
	}

	else if (key == /*0x07C*/0xff53)
	{
		wolf3d->player.angle += M_PI/48;
	}
	else if (key ==/*0x07B*/0xff51)
	{
		wolf3d->player.angle -= M_PI/48;
	}
	else if (key ==/*0x07E*/0xff52)
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
	else if (key ==/*0x07D*/0xff54)
	{
		if (get_tile(wolf3d->player.pos_x - 0.3*cos(wolf3d->player.angle), wolf3d->player.pos_y - 0.3*sin(wolf3d->player.angle), wolf3d) <= 0)
		{
			wolf3d->player.pos_x -= 0.3*cos(wolf3d->player.angle);
			wolf3d->player.pos_y -= 0.3*sin(wolf3d->player.angle);
			wolf3d->door = 0;
		}
	}

	else if (key == /*0x03*/0x66)
	{
		if (wolf3d->door)
			wolf3d_init(wolf3d, "maps/simple");

	}


	provider(wolf3d);
}
