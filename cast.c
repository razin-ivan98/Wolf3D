/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:30:05 by chorange          #+#    #+#             */
/*   Updated: 2019/04/17 18:26:16 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	cast_x_2(t_cast *cast, t_wolf3d *wolf3d)
{
	float cos_a;

	cos_a = wolf3d->curr_cast.cos_a;
	while (cast->new_x > 0.0 && cast->new_y > 0.0 &&
		cast->new_y < (float)wolf3d->rows && cast->new_x < (float)wolf3d->cols)
	{
		if ((cast->type = get_tile(cast->new_x + (cos_a > 0 ? 0.001 : -0.001),
							cast->new_y, wolf3d)) > 0)
			break ;
		cast->new_x += (cos_a > 0 ? 1.0 : -1.0);
		cast->new_y += (cos_a > 0 ? cast->d : -cast->d);
	}
	cast->distance = sqrt(pow((wolf3d->player.pos_x - cast->new_x), 2) +
							pow((wolf3d->player.pos_y - cast->new_y), 2));
	cast->compas = (cos_a > 0 ? east : west);
}

static void	cast_y_2(t_cast *cast, t_wolf3d *wolf3d)
{
	float sin_a;

	sin_a = wolf3d->curr_cast.sin_a;
	while (cast->new_x > 0.0 && cast->new_y > 0.0 &&
		cast->new_y < (float)wolf3d->rows && cast->new_x < (float)wolf3d->cols)
	{
		if ((cast->type = get_tile(cast->new_x, cast->new_y +
					(sin_a > 0 ? 0.001 : -0.001), wolf3d)) > 0)
			break ;
		cast->new_y += (sin_a > 0 ? 1.0 : -1.0);
		cast->new_x += (sin_a > 0 ? cast->d : -cast->d);
	}
	cast->distance = sqrt(pow((wolf3d->player.pos_x - cast->new_x), 2) +
						pow((wolf3d->player.pos_y - cast->new_y), 2));
	cast->compas = (sin_a > 0 ? south : north);
}

static void	cast_x(t_wolf3d *wolf3d)
{
	t_cast cast;

	cast.d = wolf3d->curr_cast.tan_a;
	cast.new_x = floor(wolf3d->player.pos_x) +
				(wolf3d->curr_cast.cos_a > 0.0 ? 1.0 : 0.0);
	cast.new_y = wolf3d->player.pos_y +
				(cast.new_x - wolf3d->player.pos_x) * cast.d;
	cast_x_2(&cast, wolf3d);
	wolf3d->curr_cast.col = ((cast.new_y - floor(cast.new_y)) *
				wolf3d->tex_size);
	wolf3d->curr_cast.compas = cast.compas;
	wolf3d->curr_cast.intersect_x = cast.new_x;
	wolf3d->curr_cast.intersect_y = cast.new_y;
	wolf3d->curr_cast.distance = cast.distance;
	wolf3d->curr_cast.type = cast.type;
}

static void	cast_y(t_wolf3d *wolf3d)
{
	t_cast cast;

	cast.d = 1.0 / wolf3d->curr_cast.tan_a;
	cast.new_y = floor(wolf3d->player.pos_y) +
				(wolf3d->curr_cast.sin_a > 0.0 ? 1.0 : 0.0);
	cast.new_x = wolf3d->player.pos_x +
				(cast.new_y - wolf3d->player.pos_y) * cast.d;
	cast_y_2(&cast, wolf3d);
	if (cast.distance < wolf3d->curr_cast.distance)
	{
		wolf3d->curr_cast.col = ((cast.new_x - floor(cast.new_x)) *
				wolf3d->tex_size);
		wolf3d->curr_cast.compas = cast.compas;
		wolf3d->curr_cast.intersect_x = cast.new_x;
		wolf3d->curr_cast.intersect_y = cast.new_y;
		wolf3d->curr_cast.distance = cast.distance;
		wolf3d->curr_cast.type = cast.type;
	}
}

void		cast(t_wolf3d *wolf3d)
{
	wolf3d->curr_cast.distance = 9999.9;
	if (wolf3d->curr_cast.cos_a != 0)
		cast_x(wolf3d);
	if (wolf3d->curr_cast.sin_a != 0)
		cast_y(wolf3d);
}
