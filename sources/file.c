/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:27:13 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/01 20:18:19 by Erkka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#define MAX_READ 545

// Takes the starting index of the piece as parameter 'buf'
static t_piece	*get_piece(char *buf, int id)
{
	size_t	i;

	i = 0;
	while (i < 20)
	{
		if (buf[i] == '#')
		{
			ft_putstr("# found, number: ");
			// Remember to convert id into char when assigning to pieces[]
			ft_putnbr(id);
			ft_putendl("");
		}
		i++;
	}
	return (NULL);
	/*return (pieces);*/
}

static int	extract(t_piece *pieces, char *buf, ssize_t ret)
{

	size_t	total_pieces;
	size_t	nth_piece;

	
	total_pieces = (ret + 1) / 21;
	nth_piece = 0;
	while (nth_piece < total_pieces)
	{
		pieces[nth_piece] = *get_piece(&buf[nth_piece * 20], nth_piece);
		nth_piece++;
	}
	return (0);
}

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

static int	verify(char *buf, ssize_t ret)
{
	if (ret > MAX_READ)
		return (error(FILE_MAX));
	if ((ret + 1) % 21 != 0)
		return (error(FILE_FORMAT));
	if (invalid_chars(&buf[0], ret))
		return (error(INVALID_CHARS));
	return (0);
}

int	extract_file(const char *file, t_piece *pieces)
{
	static char	buf[MAX_READ + 1];
	int			fd;
	ssize_t		ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error(OPEN_FAIL));
	ret = read(fd, buf, MAX_READ + 1);
	if (ret < 0)
		return (error(READ_FAIL));
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	buf[ret] = 0;
	if (verify(&buf[0], ret) == -1)
		return (-1);
	if (extract(pieces, &buf[0], ret) == -1)
		return (-1);
	return (0);
}
