/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:09:06 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/30 13:10:36 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	ft_lst_append(t_piece **alst, t_piece *new)
{
	if (*alst == NULL)
		*alst = new;
	else
	{
		while ((*alst)->next != NULL)
			*alst = (*alst)->next;
		(*alst)->next = new;
	}
}

// Takes the starting index of the piece as parameter 'buf'
static t_piece	*get_piece(char *buf, ssize_t ret, char id)
{
	t_piece	*piece;
	size_t	i;

	piece = NULL;
	// piece = new_piece(id);
	// if (!piece)
		// return (NULL);
	i = 0;
	while (i < 20)
	{
		if (buf[i] == '#')
		{
			ft_putstr("# found, number: ");
			ft_putnbr(id - 'A');
		}
	}
	return (piece);
}

// This function is to be separated to a new file
int	collect_pieces(char *buf, ssize_t ret)
{

	size_t	total_pieces;
	size_t	nth_piece;

	total_pieces = (ret + 1) / 21;
	nth_piece = 0;
	while (nth_piece < total_pieces)
	{
		get_piece(&buf[nth_piece * 20], ret, nth_piece + 'A');
		nth_piece++;
	}
}
