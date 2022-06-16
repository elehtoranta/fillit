/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:41:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/16 18:13:48 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Takes the char array 'solution' and simply prints it to the standard output.
 * NOTE: ft_putmem takes a memory area, interprets it as char and prints to
 * stdout for n amount of chars.
 */
static void	print_solution(char *solution, int area)
{
	uint8_t	i;

	i = 0;
	while (i < area)
	{
		ft_putmem(solution + (i * BOARD_SIZE), (size_t)area);
		ft_putchar('\n');
		i++;
	}
}

/*
 * Populates the char array 'solution' with the pieces, represented by their
 * ID's, respectively.
 */
static void	set_solution(t_piece *p, char *s)
{
	uint8_t		x;
	uint8_t		y;
	uint8_t		shift;
	uint8_t		offset;

	while (p->id != 0)
	{
		x = (uint8_t)(p->pos >> 4);
		y = (uint8_t)(p->pos & 0xf);
		shift = 15;
		while (shift < PIECE_BITS)
		{
			while (shift % 16 != 0)
			{
				if (p->piece & (1L << shift))
				{
					offset = 15 - (shift % 16);
					s[(y * 16 + (shift - (shift % 16))) + x + offset] = p->id;
				}
				shift--;
			}
			shift += 31;
		}
		p++;
	}
}

/*
 * The brawn of the program: (backtracking) recursive algorithm that
 * brute forces through the pieces and resolves the smallest formation
 * possible for the given set of pieces.
 * 
 * The solver uses nesting to iterate through X and Y planes, checks
 * if a piece can be placed to those coordinates, places it, tries to
 * solve for the next piece, and if that doesn't work, tries to find
 * a new place for this piece and repeats.
 */
static int	solve(t_piece *p, uint16_t *board, int area, uint8_t x)
{
	uint8_t	y;

	if (p->id == 0)
		return (1);
	y = 0;
	while (y + p->height <= area)
	{
		while (x + p->width <= area)
		{
			if ((*(uint64_t *)&board[y] & p->piece >> x) == 0)
			{
				*(uint64_t *)&board[y] ^= p->piece >> x;
				p->pos = (uint16_t)(x << 4 | y);
				if (solve(p + 1, board, area, 0) == 1)
					return (1);
				*(uint64_t *)&board[y] ^= p->piece >> x;
				p->pos = NOT_PLACED;
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

/*
 *Driver for a recursive solver. Extends the solve area if a solution is not
 *found for area n - 1
 */
void	solve_driver(t_piece *pieces, uint16_t *board, int piece_total)
{
	int			area;
	static char	solution[BOARD_SIZE * BOARD_SIZE];

	ft_memset(solution, '.', BOARD_SIZE * BOARD_SIZE + BOARD_SIZE);
	area = 2;
	while (area * area < piece_total * 4)
		area++;
	while (solve(pieces, board, area, 0) != 1 && area <= BOARD_SIZE)
	{
		ft_bzero(board, 2 * BOARD_SIZE);
		area++;
	}
	set_solution(pieces, &solution[0]);
	print_solution(&solution[0], area);
}
