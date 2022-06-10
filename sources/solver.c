/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:41:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/10 19:20:53 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*Sorry for the bad variable names, but this is about to get tight as fuck.*/
static int	solve(t_piece *p, uint16_t *b, uint8_t area, t_piece *prev)
{
	/*Accept*/
	if (p->id == 0)
		return (1);
	if (solve(pieces, board, area) == 1)
		update_solution();

	while (p->y + p->height < area)
	{
		while (*(uint64_t *)&b[p->y] & (p->piece >> p->x))
		{
			
		}
		*(uint64_t *)&b[p->y] ^= //
	}
}

/*
 *Driver for a recursive solver. Extends the solve area if a solution is not
 *found for area n - 1
 */
int	solve_driver(t_piece *pieces, uint16_t *board, uint8_t piece_total)
{
	uint8_t	area;

	area = ft_nat_sqrt(piece_total * 4);
	while (solve(pieces, board, area) != 1)
		area++;
}
