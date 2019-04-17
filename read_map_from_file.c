/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_from_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:20:24 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/17 18:13:10 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		errors_handling(t_wolf3d *wolf3d, char *file_name, int *fd)
{
	if ((*fd = open(file_name, O_RDONLY)) < 0)
		err_exit(wolf3d);
	if ((get_next_line(*fd, &wolf3d->line)) < 0)
		err_exit(wolf3d);
	if ((wolf3d->cols = ft_atoi(wolf3d->line)) < 3)
		err_exit(wolf3d);
	ft_strdel(&wolf3d->line);
	if ((get_next_line(*fd, &wolf3d->line)) < 0)
		err_exit(wolf3d);
	if ((wolf3d->rows = ft_atoi(wolf3d->line)) < 3)
		err_exit(wolf3d);
	ft_strdel(&wolf3d->line);
	if ((get_next_line(*fd, &wolf3d->line)) < 0)
		err_exit(wolf3d);
	ft_strdel(&wolf3d->line);
	allocate_arr(wolf3d);
}

static void		skip_whitespaces(t_wolf3d *wolf3d, int i, char **ptr)
{
	**ptr = 0;
	if (!(*ptr = ft_strchr(wolf3d->line, ' ')))
		err_exit(wolf3d);
	while (**ptr == ' ')
		(*ptr)++;
	if ((wolf3d->doors[i].pos_x = (float)ft_atoi(*ptr) + 0.5) < 1.5)
		err_exit(wolf3d);
	if (!(*ptr = ft_strchr(*ptr, ' ')))
		err_exit(wolf3d);
	while (**ptr == ' ')
		(*ptr)++;
}

static void		normed_file_read(t_wolf3d *wolf3d, int fd)
{
	int		i;
	char	*ptr;
	int		ret;

	i = 0;
	while (1)
	{
		if ((ret = get_next_line(fd, &wolf3d->line)) < 0)
			err_exit(wolf3d);
		if (!ret)
			break ;
		ft_strcpy((wolf3d->doors[i].file_name), wolf3d->line);
		if (!(ptr = ft_strchr(wolf3d->doors[i].file_name, ' ')))
			err_exit(wolf3d);
		skip_whitespaces(wolf3d, i, &ptr);
		if ((wolf3d->doors[i].pos_y = (float)ft_atoi(ptr) + 0.5) < 1.5)
			err_exit(wolf3d);
		ft_strdel(&wolf3d->line);
		i++;
	}
}

void			read_map_from_file(t_wolf3d *wolf3d, char *file_name)
{
	int		fd;
	int		row;

	errors_handling(wolf3d, file_name, &fd);
	row = 0;
	while (row < wolf3d->rows)
	{
		if ((get_next_line(fd, &wolf3d->line)) < 0)
			err_exit(wolf3d);
		parse_string(wolf3d, wolf3d->line, row);
		ft_strdel(&wolf3d->line);
		row++;
	}
	if ((get_next_line(fd, &wolf3d->line)) < 0)
		err_exit(wolf3d);
	ft_strdel(&wolf3d->line);
	normed_file_read(wolf3d, fd);
	close(fd);
}
