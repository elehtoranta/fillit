/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:27:13 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/17 14:26:18 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Find the number of contacting blocks. This function is called for each
 * block individually. The resulting number in the caller has to be
 * 6 OR 8 contacts exactly, or the tetrimino is invalid and the
 * program must terminate with an error.
 *
 * Checking is done clockwise. The first check is for out-of-bounds,
 * the second for the actual hash.
 */
static int	count_contacts(const char *buf, uint8_t i, uint8_t contacts)
{
	if (i >= 5 && *(buf - 5) == '#')
		contacts++;
	if (i % 5 < 4 && *(buf + 1) == '#')
		contacts++;
	if (i < 15 && *(buf + 5) == '#')
		contacts++;
	if (i % 5 > 0 && *(buf - 1) == '#')
		contacts++;
	return (contacts);
}

static int	is_good_piece(const char *buf, uint8_t hashes, uint8_t contacts)
{
	uint8_t	i;

	i = 0;
	while (i < PIECE_READ - 1)
	{
		if (i % 5 < 4 && (buf[i] != '#' && buf[i] != '.'))
			return (error(BAD_PIECE_FORMAT));
		if (i % 5 == 4 && buf[i] != '\n')
			return (error(BAD_PIECE_FORMAT));
		if (buf[i] == '#')
		{
			hashes++;
			contacts += count_contacts(&buf[i], i, 0);
		}
		i++;
	}
	if (hashes != 4)
		return (error(BAD_HASH_COUNT));
	if (contacts != 6 && contacts != 8)
		return (error(BAD_PIECE_CONNECTION));
	return (0);
}

static int	validate_pieces(const char *buf, ssize_t ret)
{
	uint16_t	i;

	i = 0;
	while (i < ret)
	{
		if (is_good_piece(&buf[i], 0, 0) == -1)
			return (-1);
		i += PIECE_READ;
		if (buf[i - 1] != '\n' && i < ret && i > 0)
			return (error(MISSING_NEWLINE));
	}
	return (0);
}

int	validate_file(const char *file, char *buf)
{
	int		fd;
	ssize_t	ret;
	int		total_pieces;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error(OPEN_FAIL));
	ret = read(fd, buf, MAX_READ + 1);
	if (ret <= 0)
		return (error(READ_FAIL));
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	buf[ret] = 0;
	if (ret > MAX_READ)
		return (error(FILE_MAX));
	if ((ret + 1) % 21 != 0 && ret % 21 != 0)
		return (error(FILE_FORMAT));
	total_pieces = (int)((ret + 1) / 21);
	if (validate_pieces(buf, ret) == -1)
		return (-1);
	return (total_pieces);
}
