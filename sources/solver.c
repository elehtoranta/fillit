/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:41:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/10 19:24:17 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	print_board(uint16_t *board)
{
	int	j;
	int	i;

	j = 0;
	while (j < BOARD_SIZE)
	{
		i = MAX_SHIFT;
		while (i >= 0)
		{
			/*Remember to cast the literal 1 to LONG!*/
			if (board[j] & 1L << i)
				printf("#");
			else
				printf(".");
			i--;
		}
		printf("\n");
		j++;
	}
	printf("\n");
}

/*if (piece_fits(&board[p->y], p->piece, p->x))*/
/*toggle_place(p->piece, &board[p->y], p->x);*/
/*toggle_place(p->piece, &board[p->y], p->x);*/
/*
 *static void	toggle_place(uint64_t piece, uint16_t *board, uint8_t x)
 *{
 *        *(uint64_t *)board ^= piece >> x;
 *}
 *
 *static int	piece_fits(uint16_t *board, uint64_t piece, uint8_t x)
 *{
 *    return ((*(uint64_t *)board & piece >> x) == 0);
 *}
 */

/*
 *static void	update_solution()
 *{
 *
 *}
 */


static int	solve(t_piece *p, uint16_t *board, int area)
{
	if (p->id == 0)
		return (1);
	/*while (p->id != 0)*/
	/*{*/
	while (p->y + p->height <= area)
	{
		while (p->x + p->width <= area)
		{
			if ((*(uint64_t *)&board[p->y] & p->piece >> p->x) == 0)
			{
				*(uint64_t *)&board[p->y] ^= p->piece >> p->x;
				/*https://stackoverflow.com/questions/4816322/mapping-x-y-to-single-number-value*/
				p->pos = ((uint16_t) p->x) << 8 | p->y;
				if (solve(p + 1, &board[0], area) == 1)
					return (1);
				*(uint64_t *)&board[p->y] ^= p->piece >> p->x;
				p->pos = 0;
			}
			(p->x)++;
		}
		(p->x) = 0;
		(p->y)++;
	}
	p->x = 0;
	p->y = 0;
		/*p++;*/
	/*}*/
	return (0);
}

/*
 *static int	populate(t_piece *p, uint16_t *board, int area)
 *{
 *    t_piece *current;
 *
 *    if (p->id == 0)
 *        return (1); //accept
 *    if (!piece_fits(board, p->piece, p->x))
 *        return (0);
 *    current = p;
 *    while (current)
 *    {
 *        populate(current, board, area);
 *        current++;
 *    }
 *
 *}
 */

/*Sorry for the bad variable names, but this is about to get tight as fuck.*/
/*
 *static int	solve(t_piece *p, uint16_t *b, uint8_t area, t_piece *prev)
 *{
 *    [>Accept<]
 *    if (p->id == 0)
 *        return (1);
 *    if (solve(pieces, board, area) == 1)
 *        update_solution();
 *
 *    while (p->y + p->height < area)
 *    {
 *        while (*(uint64_t *)&b[p->y] & (p->piece >> p->x))
 *        {
 *            
 *        }
 *        *(uint64_t *)&b[p->y] ^= //
 *    }
 *}
 */

/*
 *static void	print_board(uint16_t *board, t_piece *pieces, int area)
 *{
 *    int	j;
 *    int	i;
 *    int	nth;
 *
 *    nth = 0;
 *    j = 0;
 *    while (j < BOARD_SIZE)
 *    {
 *        i = MAX_SHIFT;
 *        while (i >= 0)
 *        {
 *            [>Remember to cast the literal 1 to LONG!<]
 *            if (board[j] & 1L << i)
 *            {
 *                while (piece)
 *                //printf("#");
 *            }
 *            else
 *                printf(".");
 *            i--;
        }
 *        printf("\n");
 *        j++;
 *    }
 *    printf("\n");
 *}
 */

/*
 *static uint64_t	flip_piece(uint64_t piece)
 *{
 *    int	i;
 *
 *    i = 0;
 *    while (i < PIECE_BITS)
 *}
 */

/*https://stackoverflow.com/questions/4816322/mapping-x-y-to-single-number-value*/
static void	print_solution(uint16_t *board, t_piece *p, char *solution, int area)
{
	uint8_t		x;
	uint8_t		y;
	uint8_t		shift;
	uint8_t		offset;

	while (p->id != 0)
	{
		x = (uint8_t)(p->pos >> 8);
		y = (uint8_t)(p->pos & 0xff);
		printf("Position for id %c: %hu\n", p->id, p->pos);
		printf("X for id %c: %hu\n", p->id, x);
		printf("Y for id %c: %hu\n", p->id, y);

		/*Align with top*/
		/*
		 *while ((p->piece & 0xFFFF000000000000L) == 0)
		 *    p->piece <<= BOARD_SIZE;
		 */
		shift = 15;
		while (shift < PIECE_BITS)
		{
			while (shift % 16 != 0)
			{
				/*printf("%hu ", shift);*/
				if (p->piece & (1L << shift))
				{
					offset = 15 - (shift % 16);
					printf("INSIDE, shift: %hu, x: %hu, y: %hu, offset: %hu\n", shift, p->x, p->y, offset);
					/*solution[ (p->y * 16) + ((3 - (shift / 16)) * 16) + (p->x + (16 - (shift % 16))) ] = p->id;*/
					printf("Solution placement at %hu\n", p->y * 16 + (shift - (shift % 16)) + p->x + offset);
					solution[ (p->y * 16 + (shift - (shift % 16))) + p->x + offset ] = p->id;
					/*printf("%d\n", p->y * 16 + p->x + (shift - (shift % 16)));*/
					/*printf("ROW %d\n", (3 - (shift / 16)) * 16); // row*/
				}
				shift--;
			}
			shift += 31;
		}
		p++;
	}
	ft_putendl("");
	shift = 0;
	while (shift < area)
	{
		ft_putmem(solution + (shift * BOARD_SIZE), area);
		ft_putendl("");
		shift++;
	}
}

/*
 *Driver for a recursive solver. Extends the solve area if a solution is not
 *found for area n - 1
 */
int	solve_driver(t_piece *pieces, uint16_t *board, int piece_total)
{
	int	area;
	/*solution is 16x16 grid char array (not C string)*/
	static char	solution[BOARD_SIZE * BOARD_SIZE];

	/*Initialize solution as blanks (.)*/
	ft_memset(solution, '.', BOARD_SIZE * BOARD_SIZE + BOARD_SIZE);
	area = 2;
	while (area * area < piece_total * 4)
		area++;

	/*TODO Implement the checking for each root node*/
	while (solve(pieces, board, area) != 1 && area <= BOARD_SIZE)
		area++;
	printf("\nPopulated the board:\n");
	print_board(board);
	for (int i = 0; i < BOARD_SIZE; i++)
		printf("%d. value in board: %hX\n", i, board[i]);
	print_solution(board, pieces, &solution[0], area);
	return (0);
}
