#include "wolf3d.h"

void menu_image_init(t_wolf3d *wolf3d)
{
	int len;
	int endian;
	int bytes;

	bytes = 8;
	len = 300;
	endian = 0;

	wolf3d->menu_win_ptr = mlx_new_window(wolf3d->mlx_ptr, 300, 500, "Wolf3d");

	wolf3d->menu.image = mlx_new_image(wolf3d->mlx_ptr, 300, 500);
	wolf3d->menu.image_data = mlx_get_data_addr(wolf3d->menu.image, &bytes, &len, &endian);
	wolf3d->menu.len = 300;

}

int exit_full(void)
{
	exit(1);
}

int menu_key_pressed(int key, t_wolf3d *wolf3d)
{
	if (key == 0x35)
	{
		exit(1);
	}
	else if (key == 0x7E)
	{
		if (wolf3d->menu_selected > 0)
			wolf3d->menu_selected--;
	}
	else if (key == 0x7D)
	{
		if (wolf3d->menu_selected < 3)
			wolf3d->menu_selected++;
	}

	else if (key == 0x24)
	{
		if (wolf3d->menu_selected == 0)
			wolf3d->hd = wolf3d->hd ? 0 : 1;
		else if (wolf3d->menu_selected == 1)
			wolf3d->walls_mode = wolf3d->walls_mode ? 0 : 1;
		else if (wolf3d->menu_selected == 2)
		{
			mlx_destroy_window(wolf3d->mlx_ptr, wolf3d->menu_win_ptr);
			run_game(wolf3d);
		}
		else if (wolf3d->menu_selected == 3)
		{
			exit(1);
		}
	}

	/*
	wolf3d->hd = 1024;
	mlx_destroy_window(wolf3d->mlx_ptr, wolf3d->menu_win_ptr);
	run_game(wolf3d);*/
	menu_provider(wolf3d);
}


void menu_provider(t_wolf3d *wolf3d)
{
	int i;
	int j;


	i = 0;
	while (i < 300)
	{
		j = 0;
		while (j < 500)
		{
			put_point_to_image(&wolf3d->menu, i, j, color_to_rgb(0xFFFF00));
			j++;
		}
		i++;
	}




	mlx_put_image_to_window(wolf3d->mlx_ptr, wolf3d->menu_win_ptr, wolf3d->menu.image, 0, 0);

	mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr, 120, 20, 0x555500, "Wolf3D");
	if (wolf3d->hd)
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr, 60, 50, wolf3d->menu_selected == 0 ? 0xFF0000 : 0x555500, "HD textures enable");
	else
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr, 60, 50, wolf3d->menu_selected == 0 ? 0xFF0000 : 0x555500, "HD textures disable");

	if (wolf3d->walls_mode)
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr, 60, 80, wolf3d->menu_selected == 1 ? 0xFF0000 : 0x555500, "compas textures enable");
	else
		mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr, 60, 80, wolf3d->menu_selected == 1 ? 0xFF0000 : 0x555500, "compas textures disable");

	mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr, 60, 110, wolf3d->menu_selected == 2 ? 0xFF0000 : 0x555500, "Play");
	mlx_string_put(wolf3d->mlx_ptr, wolf3d->menu_win_ptr, 60, 140, wolf3d->menu_selected == 3 ? 0xFF0000 : 0x555500, "Exit");

}

void menu_init(t_wolf3d *wolf3d)
{



	wolf3d->menu_selected = 0;
	menu_image_init(wolf3d);



	menu_provider(wolf3d);
	mlx_hook(wolf3d->menu_win_ptr, 2, 1L << 0, menu_key_pressed, wolf3d);
	mlx_hook(wolf3d->menu_win_ptr, 17, 1L << 0, exit_full, NULL);
	mlx_loop(wolf3d->mlx_ptr);

}