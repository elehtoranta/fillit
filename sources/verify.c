/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:27:13 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/28 20:23:02 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#define MAX_READ 545

static int	invalid_chars(char *buf, ssize_t ret)
{
	size_t	i;

	i = 0;
	while (buf[i] == '.' || buf[i] == '\n' || buf[i] == '#')
		i++;
	if (i == (size_t)ret)
		return (0);
	else
		return (-1);
}

int	verify_file(const char *file)
{
	int		fd;
	char	buf[MAX_READ + 1];
	ssize_t	ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error(OPEN_FAIL));
	ret = read(fd, buf, MAX_READ + 1);
	if (ret < 0)
		return (error(READ_FAIL));
	buf[ret] = 0;
	if (ret > MAX_READ)
		return (error(FILE_MAX));
	if ((ret + 1) % 21 != 0)
		return (error(FILE_FORMAT));
	if (invalid_chars(&buf[0], ret))
		return (error(FILE_CHARS));
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	return (0);
}
