#include "wolf3d.h"

void player_init(t_wolf3d *wolf3d)
{
	wolf3d->player.pos_x = 1.5;
	wolf3d->player.pos_y = 1.5;
	wolf3d->player.angle = 0.0;
}



void texture_load(t_wolf3d *wolf3d, t_texture *texture, int w, char *file_name)
{
	int endian;
	int bytes;
	int width;
	int height;
	int len;

	bytes = 8;
	endian = 0;
	len = w;

	texture->image = mlx_xpm_file_to_image(wolf3d->mlx_ptr, file_name, &width, &height);
	texture->image_data = mlx_get_data_addr(texture->image, &bytes, &len, &endian);
	texture->len = w;
}

void textures_load(t_wolf3d *wolf3d)
{
	texture_load(wolf3d, &(wolf3d->textures[0]), wolf3d->tex_size, wolf3d->hd ? "textures_hi/stone.xpm" : "textures/stone.xpm");
	texture_load(wolf3d, &(wolf3d->textures[1]), wolf3d->tex_size, wolf3d->hd ? "textures_hi/grass.xpm" : "textures/grass.xpm");
	texture_load(wolf3d, &(wolf3d->textures[2]), wolf3d->tex_size, wolf3d->hd ? "textures_hi/brick.xpm" : "textures/brick.xpm");
	texture_load(wolf3d, &(wolf3d->textures[3]), wolf3d->tex_size, wolf3d->hd ? "textures_hi/metal.xpm" : "textures/metal.xpm");
	texture_load(wolf3d, &(wolf3d->textures[4]), wolf3d->tex_size, wolf3d->hd ? "textures_hi/wood.xpm" : "textures/wood.xpm");
	texture_load(wolf3d, &(wolf3d->textures[5]), wolf3d->tex_size, wolf3d->hd ? "textures/door.xpm" : "textures/door.xpm");

	texture_load(wolf3d, &wolf3d->skybox, 960, "textures/sky.xpm");

}

void graphics_init(t_wolf3d *wolf3d)
{
	int len;
	int endian;
	int bytes;

	bytes = 8;
	len = CW;
	endian = 0;

	wolf3d->win_ptr = mlx_new_window(wolf3d->mlx_ptr, CW, CH, "Wolf3d");
	wolf3d->image.image = mlx_new_image(wolf3d->mlx_ptr, CW, CH);
	wolf3d->image.image_data = mlx_get_data_addr(wolf3d->image.image, &bytes, &len, &endian);
	wolf3d->image.len = CW;
}

void wolf3d_init(t_wolf3d *wolf3d, char *file_name)
{
	//wolf3d->hd = 1;
	//wolf3d->walls_mode = 0;
	wolf3d->door = 0;
	wolf3d->tex_size = (wolf3d->hd ? 1024 : 32);
	if (!wolf3d->win_ptr)
		graphics_init(wolf3d);
	player_init(wolf3d);
	textures_load(wolf3d);
	read_map_from_file(wolf3d, file_name);
	init_minimap(wolf3d);
}