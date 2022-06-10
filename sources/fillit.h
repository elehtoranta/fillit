/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:28:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/10 18:10:04 by elehtora         ###   ########.fr       */
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

// Constant definitions
# define BOARD_SIZE 16
# define MAX_PIECES 26
# define PIECE_READ 21
# define MAX_SHIFT 15
# define PIECE_SHIFT 63

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
	uint8_t		x;
	uint8_t		y;
}	t_piece;

// Public function declarations
int	validate(const char *file, t_piece *pieces);
int	error(int errorcode);
int	extract(t_piece *pieces, char *buf, ssize_t ret);

#endif
