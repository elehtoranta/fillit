/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:37:26 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/30 12:58:24 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_board	*new_board(size_t solution_minimum)
{
	t_board	*board;

	board = (t_board *) malloc(sizeof(t_board));
	if (!board)
		return (NULL);
	board->width = 0;
	board->height = 0;
	// Solution_minimum assigned in caller ((ft_sqrt(4 * pieces) + 1) / 1)
	board->solution_minimum = solution_minimum;
	board->pieces = NULL;
	return (board);
}

t_piece	*new_piece(char id)
{
	t_piece	*piece;

	piece = (t_piece *) malloc(sizeof(t_piece));
	if (!piece)
		return (NULL);
	piece->id = id;
	piece->next = NULL;
	return (piece);
}
// Initialize needed (super)structures for the program
int	init(void)
{
	// Call statics and check for errors, if error -> teardown
}
