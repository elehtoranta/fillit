/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:27:13 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/06 09:34:48 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#define MAX_READ 545
#define BYTE_BITS 8
#define PIECE_READ 21
#define PIECE_BLOCKS 16
#define MAX_SHIFT 15

/*Debugging*/
/*Here we read a bit representation that is input from right to left*/
static void	print_piece_r2l(uint16_t piece)
{
	int	i;

	i = 1;
	while (i <= PIECE_BLOCKS)
	{
		if (piece & 1 << (i - 1))
			ft_putchar('#');
		else
			ft_putchar('.');
		if (i % 4 == 0) // i starts from 1 due to this clause
			ft_putendl("");
		i++;
	}
}

/*
 *[>Debugging<]
 *static void	print_piece_l2r(uint16_t piece)
 *{
 *    int	i;
 *
 *    i = sizeof(uint16_t) * BYTE_BITS - 1;
 *    while (i >= 0)
 *    {
 *        if (piece & 1 << i)
 *            ft_putchar('#');
 *        else
 *            ft_putchar('.');
 *        if (i % 4 == 0)
 *            ft_putendl("");
 *        i--;
 *    }
 *}
 */

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

	i = 0;
	row = 0;
	/*Check for piece delimiter in caller*/
	/*
	 *ft_putchar(buf[i]);
	 *ft_putendl(" at beginning of set_piece");
	 */
	while (i < PIECE_READ)
	{
		/*Debugging*/
		/*ft_putchar(buf[i]); // printing pieces from chars*/
		/*if (i % 4 == 0 && i != 0)*/
		if (buf[i] == '\n' && i > 0)
			row++;
		if (buf[i] == '#')
			piece->piece |= 1 << (i - row);
			/*piece->piece |= 1 << ((PIECE_BLOCKS - 1) - i + row);*/
		i++;
	}
	/*Debugging*/
	/*ft_putchar(id + 'A');*/
	/*ft_putendl(" (from chars)");*/
	piece->weight = 0;
	piece->id = (char)(id + 'A');
	return (0);
}

static int	extract(t_piece *pieces, char *buf, ssize_t ret)
{

	size_t	total_pieces;
	size_t	nth;

	total_pieces = (ret + 1) / PIECE_READ;
	nth = 0;
	while (nth < total_pieces)
	{
		if (set_piece(&pieces[nth], &buf[nth * PIECE_READ], nth) == -1)
			return (-1);
		print_piece_r2l(pieces[nth].piece);
		ft_putnbr(pieces[nth].piece);
		ft_putendl("");
		nth++;
	}
	return (0);
}

/*
 *static int	count_contacts(char *buf, size_t i)
 *{
 *    size_t	contacts;
 *
 *    contacts = 0;
 *    ft_putchar(buf[i - 5]);
 *    if (i >= 5 && buf[i - 5] == '#') //up
 *        contacts++;
 *    if (i % 5 < 4 && buf[i + 1] == '#') //right
 *        contacts++;
 *    if (i < 15 && buf[i + 5] == '#') //down
 *        contacts++;
 *    if (i % 5 > 0 && buf[i - 1] == '#') //left
 *        contacts++;
 *    ft_putnbr(i);
 *    ft_putnbr(contacts);
 *    return (contacts);
 *}
 */

static int	is_good_piece(char *buf, size_t hashes, size_t contacts)
{
	size_t	i;

	i = 0;
	while (i < PIECE_READ - 1)
	{
		/*ft_putchar(buf[i]); //debug*/
		if (i % 5 < 4 && (buf[i] != '#' && buf[i] != '.'))
			return (error(BAD_PIECE_FORMAT));
		if (i % 5 == 4 && buf[i] != '\n')
			return (error(BAD_PIECE_FORMAT));
		if (buf[i] == '#')
		{
			hashes++;
			if (i >= 5 && buf[i - 5] == '#') //up
				contacts++;
			if (i % 5 < 4 && buf[i + 1] == '#') //right
				contacts++;
			if (i < 15 && buf[i + 5] == '#') //down
				contacts++;
			if (i % 5 > 0 && buf[i - 1] == '#') //left
				contacts++;
			/*contacts += count_contacts(&buf[i], i);*/
		}
		i++;
	}
	if (hashes != 4)
		return (error(BAD_HASH_COUNT));
	if (contacts != 6 && contacts != 8)
		return (error(BAD_PIECE_CONNECTION));
	return (i);
}

static int	validate_pieces(char *buf, size_t ret)
{
	ssize_t	i;

	i = 0;
	while ((size_t)i < ret)
	{
		if (is_good_piece(&buf[i], 0, 0 && buf[i + 1] == '\n') == -1)
				return (-1);
		i += PIECE_READ;
		/*
		 *if (buf[i] != '\n' && (size_t)i < ret && i > 0)
		 *    return (error(MISSING_NEWLINE));
		 */
	}
	return (0);
}

/*
 *static int	invalid_chars(char *buf, ssize_t ret)
 *{
 *    size_t	i;
 *
 *    i = 0;
 *    while (buf[i] == '.' || buf[i] == '\n' || buf[i] == '#')
 *    {
 *        if (i + 1 % PIECE_READ == 0 && buf[i] != '\n' && i < (size_t)ret)
 *            return(error(MISSING_NEWLINE));
 *        i++;
 *    }
 *    if (i != (size_t)ret)
 *        return (error(INVALID_CHARS));
 *    else if (hashes != ((size_t)ret + 1) / 21 * 4)
 *        return (error(BAD_HASH_COUNT));
 *    else
 *        return (0);
 *}
 */

static int	verify(char *buf, ssize_t ret)
{
	size_t	valid;

	valid = 0;
	if (ret > MAX_READ)
		return (error(FILE_MAX));
	if ((ret + 1) % 21 != 0)
		return (error(FILE_FORMAT));
	if (validate_pieces(&buf[valid], ret) == -1)
		return (-1);
	/*
	 *if (validate_pieces(&buf[0], ret) == -1)
	 *    return (-1);
	 */
	/*
	 *if (invalid_chars(&buf[0], ret))
	 *    return (-1);
	 */
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
