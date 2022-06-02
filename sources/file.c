/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:27:13 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/02 20:01:42 by Erkka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#define MAX_READ 545
#define BYTE_BITS 8
#define PIECE_READ 21
#define PIECE_BLOCKS 16

static void	print_piece(uint16_t piece)
{
	int	i;

	i = sizeof(uint16_t) * BYTE_BITS - 1;
	while (i >= 0)
	{
		if (piece & 1 << i)
			ft_putchar('#');
		else
			ft_putchar('.');
		if (i % 4 == 0)
			ft_putendl("");
		i--;
	}
}

// Checking recursively for legitimate tetrimino, e.g. checking valid
// connections. It does so by checking counter-clockwise, starting from
// the top, for a hash # in the buffer. If a # is found, it recurses
// from the found hash's position
static int	touches(char *buf, size_t i, size_t hashes, char last)
{
	if (hashes == 4)
		return (hashes);
	if (i >= 5 && buf[i - 5] == '#' && last != 'u') // check up
		hashes = touches(&buf[i - 5], i - 5, hashes + 1, 'u');
	else if (i != 0 && i % 5 != 0 && buf[i - 1] == '#' && last != 'l')	// check left
		hashes = touches(&buf[i - 1], i - 1, hashes + 1, 'l');
	else if (i < 15 && buf[i + 5] == '#' && last != 'd') // check down
		hashes = touches(&buf[i + 5], i + 5, hashes + 1, 'd');
	else if (i % 5 < 4 && buf[i + 1] == '#' && last != 'r') // check right
		hashes = touches(&buf[i + 1], i + 1, hashes + 1, 'r');
	return (hashes);
}

// Takes the starting index of the piece as parameter 'buf'
static int	set_piece(t_piece *piece, char *buf, int id)
{
	size_t	i;
	size_t	row;
	size_t	contacts; //must be exactly 6 or 8 contacts between blocks

	i = 0;
	row = 0;
	contacts = 0;
	while (i < PIECE_READ)
	{
		if (i % 4 == 0 && i != 0)
			row++;
		if (buf[i] == '#')
		{
			if (!contacts)
				contacts += touches(&buf[i], i, contacts, '0');
			piece->piece |= 1 << ((PIECE_BLOCKS - 1) - i + row);
		}
		i++;
	}
	ft_putchar(id + 'A');
	ft_putnbr(contacts);
	if (contacts != 4)
		return (error(BAD_PIECE));
	piece->weight = 0;
	piece->id = (char)(id + 'A');
	return (0);
}

static int	extract(t_piece *pieces, char *buf, ssize_t ret)
{

	size_t	total_pieces;
	size_t	nth_piece;

	total_pieces = (ret + 1) / PIECE_READ;
	nth_piece = 0;
	while (nth_piece < total_pieces)
	{
		set_piece(&pieces[nth_piece], &buf[nth_piece * PIECE_READ], nth_piece);
		/*
		 *ft_putstr("Piece: ");
		 *ft_putchar(pieces[nth_piece].id);
		 *ft_putendl("");
		 */
		/*print_piece(pieces[nth_piece].piece);*/
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
