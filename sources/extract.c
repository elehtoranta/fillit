/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:40:34 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/16 17:51:54 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Aligns the piece to the bottom-left using AND operations.
 * The checking is made with a number representing a full
 * column at the left border and a full row at the bottom, and
 * shifting piece while those values do not overlap.
 *
 * NOTE: this aligns to the BOTTOM left, since the pieces
 * evidently get flipped again in the solver.
 */
static void	align_bottomleft(t_piece *piece)
{
	while ((piece->piece & L_BORDER) == 0)
		piece->piece <<= 1;
	while ((piece->piece & D_BORDER) == 0)
		piece->piece >>= BOARD_SIZE;
}

/*
 * Gets the minimum and maximum X and Y coordinates from a given piece.
 * Used in calculating the width and height of a given piece (see: extract())
 */
static void	measure_props(uint8_t *props, const char *buf)
{
	uint8_t	i;

	props[0] = 3;
	props[1] = 0;
	props[2] = 3;
	props[3] = 0;
	i = 0;
	while (i < PIECE_READ)
	{
		if (buf[i] == '#')
		{
			if (i % 5 < props[0])
				props[0] = i % 5;
			if (i % 5 > props[1])
				props[1] = i % 5;
			if (i / 5 < props[2])
				props[2] = i / 5;
			if (i / 5 > props[3])
				props[3] = i / 5;
		}
		i++;
	}
}

/*
 *Sets values for a single piece structure to be ready for solving.
 *
 *NOTE: the 'bitwise representation' of a piece (piece->piece)
 *is upside down (along the X axis), because the way the board is
 *represented, it gets flipped again when setting the piece on the board.
 */
static void	set_piece(t_piece *piece, char *buf, char id)
{
	uint8_t	i;
	uint8_t	row;
	uint8_t	props[4];

	piece->id = id;
	measure_props(&props[0], buf);
	piece->width = props[1] - props[0] + 1;
	piece->height = props[3] - props[2] + 1;
	piece->pos = NOT_PLACED;
	i = 0;
	row = 3;
	while (i < PIECE_READ)
	{
		if (i % 5 == 0 && i > 0)
			row--;
		if (buf[i] == '#')
			piece->piece |= 1L << (PIECE_SHIFT - (i % 5) - (BOARD_SIZE * row));
		i++;
	}
	align_bottomleft(piece);
}

/*
 *Extracts data from the input file and sets values to the piece
 *structs that are needed for solving.
 */
void	extract(t_piece *pieces, char *buf, int total_pieces)
{
	int	nth;

	nth = 0;
	while (nth < total_pieces)
	{
		set_piece(&pieces[nth], &buf[nth * PIECE_READ], (char)nth + 'A');
		nth++;
	}
}
