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

#ifndef FILLIT_H
# define FILLIT_H

/* Including user created headers for get_next_line and 42 library */
# include "../lib/libft.h"
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# define BOARD_SIZE 16

// Public function declarations
int	verify_file(const char *file);
int	error(int errorcode);

// Matching error types, error descriptions are in error.c (norm)
typedef enum e_error
{
	BAD_ARGS,
	OPEN_FAIL,
	READ_FAIL,
	FILE_MAX,
	FILE_FORMAT,
	FILE_CHARS,
	CLOSE_FAIL,
}	t_error;

typedef struct s_piece
{
	uint16_t	piece;
}	t_piece;

typedef struct s_board
{
	uint16_t	board[BOARD_SIZE];
}	t_board;
#endif
