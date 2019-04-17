/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:56:09 by chorange          #+#    #+#             */
/*   Updated: 2019/04/17 17:53:04 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_wall(t_draw *d, t_wolf3d *wolf3d, int x, float col)
{
	d->row = ((d->y - (d->ch_div_2 - d->wall_div_2)) * d->delta_wall);
	if (!wolf3d->light ||
		get_tile(wolf3d->curr_cast.intersect_x + 0.2,
						wolf3d->curr_cast.intersect_y, wolf3d) == 0 ||
		get_tile(wolf3d->curr_cast.intersect_x - 0.2,
						wolf3d->curr_cast.intersect_y, wolf3d) == 0 ||
		get_tile(wolf3d->curr_cast.intersect_x,
						wolf3d->curr_cast.intersect_y + 0.2, wolf3d) == 0 ||
		get_tile(wolf3d->curr_cast.intersect_x,
						wolf3d->curr_cast.intersect_y - 0.2, wolf3d) == 0)
		put_point_to_image(&wolf3d->image, x, d->y,
get_rgb_from_texture(col, d->row, get_true_texture(wolf3d, 0), wolf3d));
	else
		put_point_to_image(&wolf3d->image, x, d->y,
calculate_light(get_rgb_from_texture(col, d->row,
get_true_texture(wolf3d, 0), wolf3d), wolf3d->curr_cast.distance));
}

static void	draw_floor(t_draw *d, t_wolf3d *wolf3d, int x)
{
	d->floor_dist = CW / (2.0 * d->y - CH) / d->cos_ang_minus_pl;
	d->floor_x = wolf3d->player.pos_x + d->floor_dist *
						wolf3d->curr_cast.cos_a;
	d->floor_y = wolf3d->player.pos_y + d->floor_dist *
						wolf3d->curr_cast.sin_a;
	d->f_col = ((d->floor_x - (int)(d->floor_x)) * wolf3d->tex_size);
	d->f_row = ((d->floor_y - (int)(d->floor_y)) * wolf3d->tex_size);
	if (get_tile(d->floor_x, d->floor_y, wolf3d) != 0 && wolf3d->light)
		put_point_to_image(&wolf3d->image, x, d->y,
calculate_light(get_rgb_from_texture(d->f_col, d->f_row,
&(wolf3d->textures[wood]), wolf3d), d->floor_dist));
	else
		put_point_to_image(&wolf3d->image, x, d->y,
get_rgb_from_texture(d->f_col, d->f_row, &(wolf3d->textures[wood]), wolf3d));
}

static void	draw_sky(t_draw *d, t_wolf3d *wolf3d, int x)
{
	d->f_col = (wolf3d->curr_cast.angle / (2 * M_PI) * 960);
	if (d->f_col < 0.0)
		d->f_col = 960.0 * (-floor(wolf3d->curr_cast.angle / 2 / M_PI))
							+ d->f_col;
	if (d->f_col > 960.0)
		d->f_col = d->f_col - 960.0 * floor(wolf3d->curr_cast.angle / 2 / M_PI);
	d->f_row = ((float)d->y / (float)(d->ch_div_2) * 100);
	put_point_to_image(&wolf3d->image, x, d->y,
get_rgb_from_texture(d->f_col, d->f_row, &(wolf3d->skybox), wolf3d));
}

static void	draw_sky_seiling(t_draw *d, t_wolf3d *wolf3d, int x)
{
	d->floor_dist = CW / (2.0 * (CH - d->y) - CH) / d->cos_ang_minus_pl;
	d->floor_x = wolf3d->player.pos_x + d->floor_dist * wolf3d->curr_cast.cos_a;
	d->floor_y = wolf3d->player.pos_y + d->floor_dist * wolf3d->curr_cast.sin_a;
	if ((d->type = get_tile(d->floor_x, d->floor_y, wolf3d)) == 0)
		draw_sky(d, wolf3d, x);
	else
	{
		d->f_col = ((d->floor_x - (int)(d->floor_x)) * wolf3d->tex_size);
		d->f_row = ((d->floor_y - (int)(d->floor_y)) * wolf3d->tex_size);
		if (wolf3d->light)
			put_point_to_image(&wolf3d->image, x, d->y,
calculate_light(get_rgb_from_texture(d->f_col, d->f_row,
get_true_texture(wolf3d, d->type), wolf3d), d->floor_dist));
		else
			put_point_to_image(&wolf3d->image, x, d->y,
get_rgb_from_texture(d->f_col, d->f_row,
get_true_texture(wolf3d, d->type), wolf3d));
	}
}

void		draw(t_wolf3d *wolf3d, int x, int wall, float col)
{
	t_draw d;

	d.delta_wall = (float)wolf3d->tex_size / wall;
	d.cos_ang_minus_pl = cos(wolf3d->curr_cast.angle - wolf3d->player.angle);
	d.ch_div_2 = CH / 2;
	d.wall_div_2 = wall / 2;
	d.y = 0;
	while (d.y < CH)
	{
		if ((d.y >= d.ch_div_2 + d.wall_div_2 && d.y < CH) ||
						(d.y >= 0 && d.y <= d.ch_div_2 - d.wall_div_2))
		{
			if (d.y < d.ch_div_2)
				draw_sky_seiling(&d, wolf3d, x);
			else
				draw_floor(&d, wolf3d, x);
		}
		else if (d.y > d.ch_div_2 - d.wall_div_2 && d.y <= d.ch_div_2 +
						d.wall_div_2)
			draw_wall(&d, wolf3d, x, col);
		d.y++;
	}
}
