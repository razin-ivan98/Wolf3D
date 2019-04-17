/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:19:29 by dwdraugr          #+#    #+#             */
/*   Updated: 2019/04/17 18:27:22 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 21

# define MALL_CHECK(x) if (!(x)) return (-1);
# define VAL_FILE(f, l, r) if ((f) < 0 || (l) == NULL || (r) < 0) return (-1);

int						get_next_line(const int fd, char **line);

#endif
