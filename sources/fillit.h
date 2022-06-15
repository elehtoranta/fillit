/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:28:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/15 13:55:46 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

/* Including user created headers for get_next_line and 42 library */
# include "../lib/libft.h"
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
#include <stdio.h> //REMOVE

// Constant definitions
# define BOARD_SIZE 16
# define GRID_SIZE BOARD_SIZE * BOARD_SIZE
# define MAX_READ 545
# define MAX_PIECES 26
# define MAX_SHIFT 15
# define PIECE_READ 21
# define PIECE_BLOCKS 16
# define PIECE_SHIFT 63
# define PIECE_BITS 64

//Hex constants
# define NOT_PLACED 0x8000

// Matching error types, error descriptions are in error.c (norm)
typedef enum e_error
{
	BAD_ARGS,
	OPEN_FAIL,
	READ_FAIL,
	FILE_MAX,
	FILE_FORMAT,
	INVALID_CHARS,
	BAD_HASH_COUNT,
	CLOSE_FAIL,
	BAD_PIECE_CONNECTION,
	MISSING_NEWLINE,
	BAD_PIECE_FORMAT,
	NO_PRINT,
}	t_error;

typedef struct	s_piece
{
	uint64_t	piece;
	char		id;
	uint8_t		width;
	uint8_t		height;
	uint16_t	pos;
}	t_piece;

// Public function declarations
int		validate_file(const char *file, char *buf);
int		error(int errorcode);
ssize_t	extract(t_piece *pieces, char *buf, int total_pieces);
int		solve_driver(t_piece *pieces, uint16_t *board, int total_pieces);

#endif
