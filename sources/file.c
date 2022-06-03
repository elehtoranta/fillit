/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:27:13 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/03 13:31:49 by Erkka            ###   ########.fr       */
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

/*
 * Find the number of contacting blocks. This function is called for each
 * block individually. The resulting number in the caller has to be
 * 6 OR 8 contacts exactly, or the tetrimino is invalid and the
 * program must terminate with an error.
 *
 * Checking is done clockwise. The first check is for out-of-bounds,
 * the second for the actual hash.
 */
/*
 *static int	get_contacts(char *buf, size_t i)
 *{
 *    size_t	contacts;
 *
 *    contacts = 0;
 *    if (i >= 5 && *(buf - 5) == '#') //up
 *        contacts++;
 *    if (i % 5 < 4 && *(buf + 1) == '#') //right
 *        contacts++;
 *    if (i < 15 && *(buf + 5) == '#') //down
 *        contacts++;
 *    if (i % 5 > 0 && *(buf - 1) == '#') //left
 *        contacts++;
 *    return (contacts);
 *}
 */


// Takes the starting index of the piece as parameter 'buf'
static int	set_piece(t_piece *piece, char *buf, int id)
{
	size_t	i;
	size_t	row;
	size_t	contacts;

	i = 0;
	row = 0;
	contacts = 0;
	while (i < PIECE_READ)
	{
		/*ft_putchar(buf[i]); // printing pieces from chars*/
		if (i % 4 == 0 && i != 0)
			row++;
		if (buf[i] == '#')
		{
			if (i >= 5 && buf[i - 5] == '#') //up
				contacts++;
			if (i % 5 < 4 && buf[i + 1] == '#') //right
				contacts++;
			if (i < 15 && buf[i + 5] == '#') //down
				contacts++;
			if (i % 5 > 0 && buf[i - 1] == '#') //left
				contacts++;
			piece->piece |= 1 << ((PIECE_BLOCKS - 1) - i + row);
		}
		i++;
	}
	ft_putchar(id + 'A');
	ft_putnbr(contacts);
	ft_putendl("");
	if (contacts != 6 && contacts != 8)
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
		print_piece(pieces[nth_piece].piece);
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
