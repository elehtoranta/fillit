/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:28:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/30 12:55:54 by elehtora         ###   ########.fr       */
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
int		validate_file(const char *file);
int		error(int errorcode);
t_piece	*new_piece(char id);


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

#endif
