/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:40:34 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/10 18:26:37 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //remove
#include "fillit.h"
#include "utils.h" //remove

/*
 *Aligns the piece to the top-left using AND operations.
 *The checking is made with a number representing a full
 *column at the left border and a full row at the top, and
 *shifting piece while those values do not overlap.
 */
static void	align_topleft(t_piece *piece)
{
	/*Align with left side*/
	while ((piece->piece & 0x8000800080008000L) == 0)
		piece->piece <<= 1;
	/*Align with top*/
	while ((piece->piece & 0xFFFF000000000000L) == 0) //this WAS flipped somehow
		piece->piece <<= BOARD_SIZE;
	/*Debug*/
	printf(" >> Piece aligned: %llX\n", piece->piece);
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
			if (i % 4 < props[0])
				props[0] = i % 4;
			if (i % 4 > props[1])
				props[1] = i % 4;
			if (i / 4 < props[2])
				props[2] = i / 4;
			if (i / 4 > props[3])
				props[3] = i / 4;
		}
		i++;
	}
	/*Debug*/
	for (int j = 0; j < 4; j++)
		printf("%d", (int)props[j]);
	/*End*/
}

// Takes the starting index of the piece as parameter 'buf'
static int	set_piece(t_piece *piece, char *buf, int id)
{
	uint8_t	i;
	uint8_t	row;
	uint8_t	props[4];

	piece->id = (char)(id + 'A');
	measure_props(&props[0], buf);
	piece->width = props[1] - props[0] + 1;
	piece->height = props[3] - props[2] + 1;
	i = 0;
	row = 0;
	while (i < PIECE_READ)
	{
		if (i % 5 == 0 && i > 0)
			row++;
		if (buf[i] == '#')
			piece->piece |= 1L << (PIECE_SHIFT - (i % 5) - (BOARD_SIZE * row));
		i++;
	}
	printf("\nPiece: %llX\t\n", piece->piece);
	gui_hex(piece->piece);
	align_topleft(piece);
	gui_hex(piece->piece);
	piece->x = 0;
	piece->y = 0;
	return (0);
}

int	extract(t_piece *pieces, char *buf, ssize_t ret)
{
	size_t	total_pieces;
	size_t	nth;

	total_pieces = (ret + 1) / PIECE_READ;
	nth = 0;
	while (nth < total_pieces)
	{
		if (set_piece(&pieces[nth], &buf[nth * PIECE_READ], nth) == -1)
			return (-1);
		nth++;
	}
	return (0);
}
