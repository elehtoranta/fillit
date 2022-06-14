/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:40:34 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/13 13:53:24 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "utils.h"

/*
 *Aligns the piece to the top-left using AND operations.
 *The checking is made with a number representing a full
 *column at the left border and a full row at the top, and
 *shifting piece while those values do not overlap.
 *
 *NOTE: now this aligns to the BOTTOM LEFT, since the pieces
 *evidently get flipped again in the solver.
 */
static void	align_topleft(t_piece *piece)
{
	/*Align with left side*/
	while ((piece->piece & 0x8000800080008000L) == 0)
		piece->piece <<= 1;
	/*Align with top*/
	while ((piece->piece & 0xFFFFL) == 0) //this IS REflipped somehow
		piece->piece >>= BOARD_SIZE;
	/*Debug*/
	/*printf(" >> Piece aligned: %llX\n", piece->piece);*/
}

/*Gets the width and height of a given piece*/
static void	measure_props(uint8_t *props, const char *buf)
{
	uint8_t	i;

	props[0] = 3; //x min
	props[1] = 0; //x max
	props[2] = 3; //y min
	props[3] = 0; //y max
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
	/*Debug*/
	/*for (int j = 0; j < 4; j++)*/
		/*printf("%d", (int)props[j]);*/
	/*End*/
}

// Takes the starting index of the piece as parameter 'buf'
static int	set_piece(t_piece *piece, char *buf, char id)
{
	uint8_t	i;
	uint8_t	row;
	uint8_t	props[4];

	piece->id = id;
	measure_props(&props[0], buf);
	piece->width = props[1] - props[0] + 1;
	piece->height = props[3] - props[2] + 1;
	piece->pos = 0x8000;
	/*Debug*/
	/*printf("\nPiece %c width: %hhu, height: %hhu.\n", piece->id, piece->width, piece->height);*/
	i = 0;
	row = 3;
	/*Debug*/
	/*printf("\nThe piece in buffer:\n");*/
	/*write(1, buf, PIECE_READ);*/
	while (i < PIECE_READ)
	{
		if (i % 5 == 0 && i > 0)
			row--;
		/*
		 *The pieces are placed upside down, because the cast of board to uint64_t
		 *causes them to flip again. e.g. the pieces flip twice during execution.
		 */
		if (buf[i] == '#')
			piece->piece |= 1L << (PIECE_SHIFT - (i % 5) - (BOARD_SIZE * row));
		i++;
	}
	/*Debug*/
	/*printf("The set piece: %llX\t\n", piece->piece);*/
	/*gui_hex(piece->piece);*/
	align_topleft(piece);
	/*gui_hex(piece->piece);*/
	/*ft_putendl("");*/
	/*End*/
	piece->x = 0;
	piece->y = 0;
	return (0);
}

ssize_t	extract(t_piece *pieces, char *buf, int total_pieces)
{
	int	nth;

	nth = 0;
	printf("Count of pieces: %d\n", total_pieces);
	while (nth < total_pieces)
	{
		if (set_piece(&pieces[nth], &buf[nth * PIECE_READ], nth + 'A') == -1)
			return (-1);
		nth++;
	}
	return (0);
}
