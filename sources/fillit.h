/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:28:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/16 18:09:22 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

/* Including user created headers for get_next_line and 42 library */
# include "../libft/libft.h"
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>

// Constant definitions
# define BOARD_SIZE 16
# define MAX_READ 545
# define MAX_PIECES 26
# define PIECE_READ 21
# define PIECE_SHIFT 63
# define PIECE_BITS 64

//Hex constants
# define NOT_PLACED 0x8000
# define L_BORDER 0x8000800080008000L
# define D_BORDER 0xFFFFL

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
}	t_error;

typedef struct s_piece
{
	uint64_t	piece;
	char		id;
	uint8_t		width;
	uint8_t		height;
	uint16_t	pos;
}				t_piece;

// Public function declarations
int		validate_file(const char *file, char *buf);
int		error(int errorcode);
void	extract(t_piece *pieces, char *buf, int total_pieces);
void	solve_driver(t_piece *pieces, uint16_t *board, int total_pieces);

#endif
