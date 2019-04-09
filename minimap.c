#include "wolf3d.h"

void create_minimap(t_wolf3d *wolf3d)
{
	int i;
	int j;

	i = 0;
	while (i < (wolf3d->cols * 8))
	{
		j = 0;
		while(j < (wolf3d->rows * 8))
		{
			if (get_tile(((float)i)/8, ((float)j)/8, wolf3d) == 9)
				put_point_to_image(&wolf3d->minimap, i, j, color_to_rgb(0x0000FF));
			else if (get_tile(((float)i)/8, ((float)j)/8, wolf3d) > 0)
				put_point_to_image(&wolf3d->minimap, i, j, color_to_rgb(0x00FF00));
			else
				put_point_to_image(&wolf3d->minimap, i, j, color_to_rgb(0xFFFF00));
			j++;
		}
		i++;
	}
}

void init_minimap(t_wolf3d *wolf3d)
{
	int len;
	int endian;
	int bytes;
	int width;
	int height;

	bytes = 8;
	len = wolf3d->cols * 8;
	endian = 0;

	wolf3d->minimap.image = mlx_new_image(wolf3d->mlx_ptr, wolf3d->cols * 8, wolf3d->rows * 8);
	wolf3d->minimap.image_data = mlx_get_data_addr(wolf3d->minimap.image, &bytes, &len, &endian);
	wolf3d->minimap.len = wolf3d->cols * 8;
	create_minimap(wolf3d);
}



void draw_minimap(t_wolf3d *wolf3d)
{

	int i;
	int j;
	int x;
	int y;

	i = 0;
	x = (int)(wolf3d->player.pos_x * 8 + 16);
	y = (int)(wolf3d->player.pos_y * 8 + 16);
	mlx_put_image_to_window(wolf3d->mlx_ptr, wolf3d->win_ptr, wolf3d->minimap.image, 20, 20);
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			mlx_pixel_put(wolf3d->mlx_ptr, wolf3d->win_ptr, x + i, y + j, 0xFF0000);
			j++;
		}
		i++;
	}

}