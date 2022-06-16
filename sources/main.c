/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:21:53 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/16 18:10:10 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Main calls the 3 core functions of the program, that (1) check if the file
 * given as input is valid acccording to the specification given in the subject;
 * (2) Extracts the data needed to solve the smallest square given the set of
 * tetriminos (or 'pieces'); (3) Solves the smallest square using a backtracking
 * algorithm.
 */
int	main(int argc, char **argv)
{
	static t_piece	pieces[MAX_PIECES + 1];
	static char		buf[MAX_READ + 1];
	static uint16_t	board[BOARD_SIZE];
	int				total_pieces;

	if (argc != 2)
		return (error(BAD_ARGS));
	total_pieces = validate_file(argv[1], &buf[0]);
	if (total_pieces == -1)
		return (-1);
	extract(&pieces[0], &buf[0], total_pieces);
	solve_driver(&pieces[0], &board[0], total_pieces);
	return (0);
}
