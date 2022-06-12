/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:21:53 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/10 15:36:18 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 *static void	copy_piece_to(char *solution, t_piece *p)
 *{
 *    uint8_t	x;
 *    uint8_t	y;
 *
 *    x = 0;
 *    y = 0;
 *    while (y < 4)
 *    {
 *        while (x < 4)
 *        {
 *            if (p->piece & 8000000000000000L >> (x + (x * y)))
 *                solution[x * (y + 1)] = p->id;
 *            x++;
 *        }
 *        y++;
 *    }
 *}
 *
 *static int	print_solution(t_piece *pieces)
 *{
 *    char	solution[BOARD_SIZE][BOARD_SIZE]; //not terminated == not strings == no string ops!
 *    uint8_t	i;
 *
 *    while (pieces->id != 0)
 *    {
 *        copy_piece_to(&solution[pieces->y][pieces->x], pieces);
 *        pieces++;
 *    }
 *    i = 0;
 *    while (i < BOARD_SIZE)
 *    {
 *        ft_putmem(solution[i], BOARD_SIZE);
 *        ft_putendl("");
 *        i++;
 *    }
 *    return (0);
 *}
 */

int	main(int argc, char **argv)
{
	static t_piece	pieces[MAX_PIECES + 1];
	static char		buf[MAX_READ + 1];
	static uint16_t	board[BOARD_SIZE];
	char			total_pieces;

	if (argc != 2)
		return (error(BAD_ARGS));
	total_pieces = validate_file(argv[1], &buf[0]);
	if (total_pieces == -1)
		return (-1);
	if (extract(&pieces[0], &buf[0], total_pieces) == -1)
		return (-1);
	if (solve_driver(&pieces[0], &board[0], total_pieces) == -1)
		return (-1);
	/*
	 *if (print_solution(&pieces[0]) == -1)
	 *    return(error(NO_PRINT));
	 */

	return (0);
}
