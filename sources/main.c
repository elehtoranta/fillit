/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:21:53 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/15 17:27:44 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Main initializes the static variables needed for most of the execution, and
 * calls all three modules of the program: file validation, data extraction,
 * and solving the puzzle.
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
	return (0);
}
