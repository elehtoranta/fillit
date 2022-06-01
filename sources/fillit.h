/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:28:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/01 20:30:14 by Erkka            ###   ########.fr       */
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

// Matching error types, error descriptions are in error.c (norm)
typedef enum e_error
{
	BAD_ARGS,
	OPEN_FAIL,
	READ_FAIL,
	FILE_MAX,
	FILE_FORMAT,
	INVALID_CHARS,
	CLOSE_FAIL,
}	t_error;

typedef struct s_piece
{
	char			id;
	// int	ordering_weight;
	uint8_t			piece[4][2];
	struct s_piece	*next;
}	t_piece;

typedef struct s_board
{
	char	board[BOARD_SIZE][BOARD_SIZE];
	t_piece *pieces;
	size_t	width;
	size_t	height;
	size_t	solution_minimum;
}	t_board;

// Public function declarations
int		extract_file(const char *file, t_piece *pieces);
int		error(int errorcode);
int		teardown(void);
t_piece	*new_piece(char id);

#endif
