/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teardown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:43:50 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/31 16:21:54 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	*free_pieces(t_piece **p_pieces)
{
	t_piece	*next;

	next = *p_pieces;
	while ((*p_pieces)->next)
	{
		next = (*p_pieces)->next;
		free(*p_pieces);
		*p_pieces = NULL;
		*p_pieces = next;
	}
	p_pieces = NULL;
}

// Frees memory of allocated members
int	teardown(t_board *b)
{

}
