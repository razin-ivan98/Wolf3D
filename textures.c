/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:53:30 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 17:57:46 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_texture		*get_true_texture(t_wolf3d *wolf3d, int type)
{
	if (!type)
		type = wolf3d->curr_cast.type;
	if (wolf3d->walls_mode && type > 0 && type < 9)
		return (&wolf3d->textures[wolf3d->curr_cast.compas]);
	else if (!wolf3d->walls_mode && type > 0 && type < 9)
		return (&wolf3d->textures[type - 1]);
	else if (type < 0)
		return (&wolf3d->textures[-type - 1]);
	else if (type > 8)
		return (&wolf3d->textures[9]);
	return (NULL);
}

static void		bilinear_filtration_2(t_bilinear *bi, float u, float v, int c)
{
	if (bi->c3 < 0)
		bi->c3 += 255;
	bi->c4 = bi->ptr[bi->i4 + c];
	if (bi->c4 < 0)
		bi->c4 += 255;
	bi->u_ratio = u - bi->x;
	bi->v_ratio = v - bi->y;
	bi->u_opposite = 1 - bi->u_ratio;
	bi->v_opposite = 1 - bi->v_ratio;
	bi->result = (int)((bi->c1 * bi->u_opposite + bi->c2 * bi->u_ratio) *
	bi->v_opposite +
	(bi->c3 * bi->u_opposite + bi->c4 * bi->u_ratio) * bi->v_ratio);
}

int				bilinear_filtration(float u, float v, t_texture *texture, int c)
{
	t_bilinear bi;

	bi.ptr = texture->image_data;
	bi.x = floor(u);
	bi.y = floor(v);
	bi.i1 = texture->len * bi.y * 4 + bi.x * 4;
	bi.i2 = texture->len * bi.y * 4 +
	((bi.x == texture->len - 1) ? 0 : (bi.x + 1)) * 4;
	bi.i3 = texture->len * ((bi.y == texture->len - 1) ?
	0 : (bi.y + 1)) * 4 + bi.x * 4;
	bi.i4 = texture->len * ((bi.y == texture->len - 1) ?
	0 : (bi.y + 1)) * 4 + ((bi.x == texture->len - 1) ? 0 : (bi.x + 1)) * 4;
	bi.c1 = bi.ptr[bi.i1 + c];
	if (bi.c1 < 0)
		bi.c1 += 255;
	bi.c2 = bi.ptr[bi.i2 + c];
	if (bi.c2 < 0)
		bi.c2 += 255;
	bi.c3 = bi.ptr[bi.i3 + c];
	bilinear_filtration_2(&bi, u, v, c);
	return (bi.result);
}

static void		get_rgb_from_texture_2(t_rgb *rgb,
t_texture *texture, float col, float row)
{
	int c;
	int r;
	int index;

	c = (int)col;
	r = (int)row;
	index = texture->len * r * 4 + c * 4;
	rgb->r = texture->image_data[index + 2];
	rgb->g = texture->image_data[index + 1];
	rgb->b = texture->image_data[index];
}

t_rgb			get_rgb_from_texture(float col, float row,
t_texture *texture, t_wolf3d *wolf3d)
{
	t_rgb	rgb;

	if (col < 0)
		col *= -1;
	if (row < 0)
		row *= -1;
	if (col >= texture->len)
		col = texture->len - 1;
	if (row >= texture->len)
		row = texture->len - 1;
	if (wolf3d->filtr)
	{
		rgb.r = bilinear_filtration(col, row, texture, 2);
		rgb.g = bilinear_filtration(col, row, texture, 1);
		rgb.b = bilinear_filtration(col, row, texture, 0);
	}
	else
		get_rgb_from_texture_2(&rgb, texture, col, row);
	return (rgb);
}
