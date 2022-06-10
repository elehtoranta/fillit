/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:31:26 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/10 17:59:05 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "fillit.h"
#include <stdio.h>

#define PIECE_BLOCKS 16

/*
 *Utility functions to use in debugging fillit
 *Defined in fillit_utils.h
 */
void	gui_hex(uint64_t piece)
{
	int	i;

	i = 0;
	while (i < BOARD_SIZE * 4)
	{
		if (i % BOARD_SIZE == 0 && i > 0)
			printf("\n");
		if (piece & 0x8000000000000000L >> i)
			printf("#");
		else
			printf(".");
		i++;
	}
	printf("\n");
}

/*Here we read a bit representation that is input from right to left*/
void	print_piece_r2l(uint16_t piece)
{
	int	i;

	i = 1;
	while (i <= PIECE_BLOCKS)
	{
		if (piece & 1 << (i - 1))
			ft_putchar('#');
		else
			ft_putchar('.');
		if (i % 4 == 0) // i starts from 1 due to this clause
			ft_putendl("");
		i++;
	}
}

void	print_piece_l2r(uint16_t piece)
{
	int	i;

	i = sizeof(uint16_t) * 8 - 1;
	while (i >= 0)
	{
		if (piece & 1 << i)
			ft_putchar('#');
		else
			ft_putchar('.');
		if (i % 4 == 0)
			ft_putendl("");
		i--;
	}
}

