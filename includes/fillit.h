/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:28:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/20 18:20:05 by Erkka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FILLIT_H_
#define _FILLIT_H_

/* Including user created headers for get_next_line and 42 library */
# include "libft.h"

# define BOARD_SIZE 16

typedef struct	s_error
{
	const char		*error_message;
	unsigned int	error_id;
}				t_error;

typedef struct	s_piece
{
	uint16_t	piece;
}				t_piece;

typedef struct	s_board
{
	uint16_t	board[BOARD_SIZE];
}				t_board;

#endif
