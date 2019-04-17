/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <cocummin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:22:51 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 14:51:59 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	parse_string(t_wolf3d *wolf3d, char *line, int row)
{
	int		col;
	char	*ptr;

	ptr = line;
	col = 0;
	while (col < wolf3d->cols)
	{
		wolf3d->map[col][row] = ft_atoi(ptr);
		if (!((wolf3d->map[col][row] >= -5 && wolf3d->map[col][row] <= 5) ||
		(wolf3d->map[col][row] >= 91 && wolf3d->map[col][row] <= 99)))
			err_exit(wolf3d);
		if ((col == 0 || col == wolf3d->cols - 1 || row == 0 ||
		row == wolf3d->rows - 1) && wolf3d->map[col][row] <= 0)
			err_exit(wolf3d);
		if (ft_strchr(ptr, ' '))
			ptr = ft_strchr(ptr, ' ');
		while (*ptr == ' ')
			ptr++;
		col++;
	}
}

void	allocate_arr(t_wolf3d *wolf3d)
{
	int i;

	i = 0;
	wolf3d->map = (int **)ft_memalloc(sizeof(int *) * wolf3d->cols);
	if (!wolf3d->map)
		err_exit(wolf3d);
	while (i < wolf3d->cols)
	{
		wolf3d->map[i] = (int *)ft_memalloc(sizeof(int) * wolf3d->rows);
		if (!wolf3d->map[i])
			err_exit(wolf3d);
		i++;
	}
}
