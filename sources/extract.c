/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:40:34 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/15 19:23:55 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Aligns the piece to the bottom-left using AND operations.
 * The checking is made with a number representing a full
 * column at the left border and a full row at the bottom, and
 * shifting piece while those values do not overlap.
 * If this doesn't make sense, I suggest looking at a programming view
 * of a calculator, giving the values as hexadecimal and looking at the
 * binary representation.
 *
 * NOTE: this aligns to the BOTTOM left, since the pieces
 * evidently get flipped again in the solver.
 */
static void	align_bottomleft(t_piece *piece)
{
	while ((piece->piece & 0x8000800080008000L) == 0)
		piece->piece <<= 1;
	while ((piece->piece & 0xFFFFL) == 0)
		piece->piece >>= BOARD_SIZE;
}

/*
 * Gets the minimum and maximum values of a piece on X and Y planes, so
 * the piece width and height can be calculated.
 *
 * Measuring starts by setting minimum and maximum values for the min,max
 * coordinates (see inline for variable 'names').
 *
 * NOTE: Remember that every 5th character is a newline (indices 4, 9, 14, 19)
 *
 * The position X:0, Y:0 is the TOP LEFT corner of a piece.
 *
 * For each found hash we calculate it's position:
 * 1. x (column) can be found with i % 5 (e.g. 1 % 5 == 1, 6 % 5 == 1, etc.)
 * 2. y (row) can be found with i / 5 (e.g. 1 / 5 == 0, 3 / 5 == 0, 6 / 5 == 1, etc.)
 */
static void	measure_props(uint8_t *props, const char *buf)
{
	uint8_t	i;

	/*These are expected to change during checking.*/
	props[0] = 3;												// x min
	props[1] = 0;												// x max
	props[2] = 3;												// y min
	props[3] = 0;												// y max
	i = 0;
	while (i < PIECE_READ)
	{
		if (buf[i] == '#')
		{
			if (i % 5 < props[0])								// Check if checked hash is at a smaller X position than current MINIMUM (default: 3)
				props[0] = i % 5;								// if TRUE, set X minimum to current hash's X coordinate
			if (i % 5 > props[1])								// Check if checked hash is at a greater X position than current MAXIMUM (default: 0)
				props[1] = i % 5;								// if TRUE, set X maximum to current hash's X coordinate
			if (i / 5 < props[2])								// Check if checked hash is at a smaller Y position than current MINIMUM (default: 3)
				props[2] = i / 5;								// if TRUE, set Y minimum to current hash's Y coordinate
			if (i / 5 > props[3])								// Check if checked hash is at a greater Y position than current MAXIMUM (default: 0)
				props[3] = i / 5;								// if TRUE, set Y maximum to current hash's Y coordinate.
		}
		i++;
	}
}

/*Takes the starting index of the piece as parameter 'buf'*/
/*
 * Sets the piece structs elements ready for solving. Reads through a buffer
 * from first character to last.
 *
 * This function is a bit funky, as it writes the piece in the piece->piece
 * element (variable named piece, inside a struct named piece) left to right and
 * UPSIDE DOWN. This means that the row that's first in the character buffer
 * is put in as the last row in the piece uint64_t.
 *
 * The above procedure is due to the weird behaviour when type casting the board
 * array from *uint16_t to *uint64_t:
 *     the row with bit indexes 15 to 0 is at board[0]
 *     row with bit positions 16 to 31 at board[1],
 *     32 to 47 at board[2] and
 *     48 to 63 at board[3].
 * This causes the pieces to flip on the X axis, i.e. upside down, when placing
 * them on the board. Hence we need to declare the pieces in the piece struct
 * upside down, so they get re-flipped while placing. This is a behaviour of
 * the array casting I can demonstrate if needed, because it took me a while to
 * figure out and a while longer to accept.
 *
 * Finally we align the piece to the bottom left corner, after which it's ready
 * for placement in the solver.
 *
 * DEF 1: Setting the piece by buffer index
 * The expression takes the variable piece from struct piece (piece->piece) and
 * does an bitwise OR assignment operation to it. The goal is to set a bit that
 * corresponds the same position the current hash is in at the buffer
 * representation of that piece.
 * > piece->piece is a uint64_t, meaning 'unsigned int with size of 64 bits'.
 * > PIECE_SHIFT is a constant of value 63: it's the maximum of times we can
 * left shift the 1L (1 with 63 leading zeroes in binary) before we're
 * out of bounds.
 * > BOARD_SIZE is 16
 * NOTE: left shifting means starting from bit position 0 (right-most position) and
 * going towards max bit position (for uint64_t it's 63; the left-most position).
 *
 * Explanation: Shifting 1L left PIECE_SHIFT amount of times would set the last bit
 * (from right to left). Hence, when we want to get the hash's X position, we
 * substract i % 5 from that max shift. To get the Y position, we substract
 * (Nth row * row length) from that result, to go N rows down from the X position.
 * Here's the brain twister - since we have to flip the pieces upside down, we
 * start at row at 3 and decrement it appropriately. This causes the first read
 * buffer row to go to the last row (bits 15 to 0) in the piece variable, and last
 * buffer row to go to the first row in the piece variable.
 */
static int	set_piece(t_piece *piece, char *buf, char id)
{
	uint8_t	i;
	uint8_t	row;
	uint8_t	props[4];

	piece->id = id;											// Set the identifier (A to Z)
	measure_props(&props[0], buf);							// Get the min,max values for X and Y of this piece
	piece->width = props[1] - props[0] + 1;					// Set width (max - min + 1). +1 is for correction: piece from index 0 to 1 is width 2, not 1 - 0 == 1.
	piece->height = props[3] - props[2] + 1;				// Set height (max - min + 1)
	piece->pos = NOT_PLACED;								// Set piece position as the default constant 0x8000. See info of NOT_PLACED in header file.
	i = 0;
	row = 3;												// Row starts from 3 and decrements, so that we can place the piece upside down, but retain the Y axis.
	while (i < PIECE_READ)									// For each character in buffer
	{
		if (i % 5 == 0 && i > 0)							// If index is at start of a new row
			row--;											// decrement row index.
		if (buf[i] == '#')									// If char at current index is a hash,
			piece->piece |= 1L << (PIECE_SHIFT - (i % 5) - (BOARD_SIZE * row));	// Set a bit to represent a hash in the 'bitwise piece' (see 1. in description)
		i++;
	}
	align_bottomleft(piece);								// Align the piece to bottom left -most position
	return (0);
}

/*
 *Loop through every piece and set their values accordingly. Since ASCII characters
 *are only integers, we can do nth + 'A' to increment the id(entifier) cleanly.
 *
 *The buffer given as parameter to set_piece() always points to the first character of
 *nth piece in the buffer.
 */
ssize_t	extract(t_piece *pieces, char *buf, int total_pieces) // TODO THIS RETURN VALUE WILL BE CHANGED
{
	int	nth;

	nth = 0;
	while (nth < total_pieces)								// Loop through all pieces
	{
		if (set_piece(&pieces[nth], &buf[nth * PIECE_READ], nth + 'A') == -1)	// Set the nth piece at the array of pieces given as parameter to extract()
			return (-1);
		nth++;
	}
	return (0);												// 0 for everything OK (this return is changed to int for final version)
}
