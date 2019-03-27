#include "wolf3d.h"

void player_init(t_wolf3d *wolf3d)
{
	wolf3d->player.pos_x = 1.5;
	wolf3d->player.pos_y = 1.5;
	wolf3d->player.angle = 0.0;
}

void textures_load(t_wolf3d *wolf3d)
{
	int len;
	int endian;
	int bytes;
	int width;
	int height;

	bytes = 8;
	len = TEX_SIZE;
	endian = 0;

	wolf3d->textures[0].image = mlx_xpm_file_to_image(wolf3d->mlx_ptr, "textures/stone.xpm", &width, &height);
	wolf3d->textures[0].image_data = mlx_get_data_addr(wolf3d->textures[0].image, &bytes, &len, &endian);
	wolf3d->textures[0].len = TEX_SIZE;

	wolf3d->textures[1].image = mlx_xpm_file_to_image(wolf3d->mlx_ptr, "textures/grass.xpm", &width, &height);
	wolf3d->textures[1].image_data = mlx_get_data_addr(wolf3d->textures[1].image, &bytes, &len, &endian);
	wolf3d->textures[1].len = TEX_SIZE;

	wolf3d->textures[2].image = mlx_xpm_file_to_image(wolf3d->mlx_ptr, "textures/brick.xpm", &width, &height);
	wolf3d->textures[2].image_data = mlx_get_data_addr(wolf3d->textures[2].image, &bytes, &len, &endian);
	wolf3d->textures[2].len = TEX_SIZE;

	wolf3d->textures[3].image = mlx_xpm_file_to_image(wolf3d->mlx_ptr, "textures/metal.xpm", &width, &height);
	wolf3d->textures[3].image_data = mlx_get_data_addr(wolf3d->textures[3].image, &bytes, &len, &endian);
	wolf3d->textures[3].len = TEX_SIZE;

	wolf3d->textures[4].image = mlx_xpm_file_to_image(wolf3d->mlx_ptr, "textures/wood.xpm", &width, &height);
	wolf3d->textures[4].image_data = mlx_get_data_addr(wolf3d->textures[4].image, &bytes, &len, &endian);
	wolf3d->textures[4].len = TEX_SIZE;

	wolf3d->textures[5].image = mlx_xpm_file_to_image(wolf3d->mlx_ptr, "textures/door.xpm", &width, &height);
	wolf3d->textures[5].image_data = mlx_get_data_addr(wolf3d->textures[5].image, &bytes, &len, &endian);
	wolf3d->textures[5].len = TEX_SIZE;

	len = 960;

	wolf3d->skybox.image = mlx_xpm_file_to_image(wolf3d->mlx_ptr, "textures/sky.xpm", &width, &height);
	wolf3d->skybox.image_data = mlx_get_data_addr(wolf3d->skybox.image, &bytes, &len, &endian);
	wolf3d->skybox.len = 960;

}

void graphics_init(t_wolf3d *wolf3d)
{
	int len;
	int endian;
	int bytes;

	bytes = 8;
	len = CW;
	endian = 0;

	wolf3d->mlx_ptr = mlx_init();
	wolf3d->win_ptr = mlx_new_window(wolf3d->mlx_ptr, CW, CH, "wolf3d");
	wolf3d->image = mlx_new_image(wolf3d->mlx_ptr, CW, CH);
	wolf3d->image_data = mlx_get_data_addr(wolf3d->image, &bytes, &len, &endian);
}

void wolf3d_init(t_wolf3d *wolf3d, char *file_name)
{
	wolf3d->walls_mode = 0;
	wolf3d->door = 0;
	if (!wolf3d->mlx_ptr)
		graphics_init(wolf3d);
	player_init(wolf3d);
	textures_load(wolf3d);
	read_map_from_file(wolf3d, file_name);
}