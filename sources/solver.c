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
	uint8_t	x;
	uint8_t	y;

	x = 0;
	y = 0;
	if (p->id == 0)
		return (1);
	/*while (p->id != 0)*/
	/*{*/
	while (y + p->height <= area)
	{
		while (x + p->width <= area)
		{
			if ((*(uint64_t *)&board[y] & p->piece >> x) == 0)
			{
				*(uint64_t *)&board[y] ^= p->piece >> x;
				/*https://stackoverflow.com/questions/4816322/mapping-x-y-to-single-number-value*/
				p->pos = ((uint16_t) x) << 8 | y;
				if (solve(p + 1, &board[0], area) == 1)
					return (1);
				*(uint64_t *)&board[y] ^= p->piece >> x;
				p->pos = 0;
			}
			(x)++;
		}
		(x) = 0;
		(y)++;
	}
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
/*https://stackoverflow.com/questions/4816322/mapping-x-y-to-single-number-value*/
static void	print_solution(uint16_t *board, t_piece *p, char *solution, int area)
{
	uint8_t		x;
	uint8_t		y;
	uint8_t		block;
	uint16_t	i;

	while (p->id != 0)
	{
		printf("Position for id %c: %hu\n", p->id, p->pos);
		x = (uint8_t)(p->pos >> 8);
		y = (uint8_t)(p->pos & 0xff);
		printf("X for id %c: %hu\n", p->id, x);
		printf("Y for id %c: %hu\n", p->id, y);

		/*Align with top*/
		while ((p->piece & 0xFFFF000000000000L) == 0)
			p->piece <<= BOARD_SIZE;
		block = 0;
		while (block < PIECE_BITS)
		{
			if (block % 4 == 0)
				block += (BOARD_SIZE - 4); //jump to x0, y+1
			if (p->piece & 1 << block)
				solution[x + (y * BOARD_SIZE)] = p->id;
			block++;
		}
		p++;
	}
	i = 0;
	while (i < area)
	{
		ft_putmem(solution + (i * BOARD_SIZE), area);
		ft_putendl("");
		i++;
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
