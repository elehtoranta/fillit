/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:27:13 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/15 18:10:14 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Find the number of contacting blocks. This function is called for each
 * block individually. The resulting number in the caller has to be
 * 6 OR 8 contacts exactly, or the tetrimino is invalid and the
 * program must terminate with an error.
 *
 * Checking is done clockwise. 
 * (1) The first check is for out-of-bounds (i.e.
 * if the hash is at top/right/bottom/left border, as we can't check from
 * outside the piece grid)
 * (2) the second check is for the actual hash.
 *
 * It's worth keeping in mind that the pointer to buf is a pointer to an already
 * found hash character, so this checking is done relative to that hash.
 */
static int	count_contacts(const char *buf, size_t i, size_t contacts)
{
	if (i >= 5 && *(buf - 5) == '#')	// Checking above
		contacts++;
	if (i % 5 < 4 && *(buf + 1) == '#')	// Checking right
		contacts++;
	if (i < 15 && *(buf + 5) == '#')	// Checking below
		contacts++;
	if (i % 5 > 0 && *(buf - 1) == '#')	// Checking left
		contacts++;
	return (contacts);
}

/*
 *The aptly named function that verifies that a single piece in the input file
 *is valid. The parameter pointer to buf is a pointer to the first character of
 *each 4x4 'tetrimino' (hereafter 'piece'), and the function iterates full 20
 *chars from that buffer, i.e. last character included.
 *
 *Remember that the buffer contains newlines, so each row of characters is total of
 *5 bytes wide.
 *
 *The first if statement checks if the first 4 characters in a row contain illegal
 *characters, and the second if checks the 5th character for a row separating
 *newline. If any illegal characters are found, program exits with 'error'
 *printed to stdout. (see error.c and fillit.h)
 *
 *If these checks pass, the character at index i is checked for a '#'.
 *If a hash is found, we add it to collector 'hashes' and get a count of it's
 *contacts or 'neighbours' from count_contacts(). (NOTE: the 0 passed as an
 *argument is just for convenience and laziness: 'contacts' variable could just
 *as well be declared in count_contacts()).
 *
 *The piece in buffer is iterated through, stopping after the last character
 *at i == 19. After this we should have total of 4 hashes counted per tetrimino,
 *and a total of 6 OR 8 contacts per tetrimino between it's blocks. (NOTE: only
 *the square piece has 8 connections, others have 6).
 *
 *If all checks pass, we return a non-negative value, and we know this piece is
 *valid.
 */
static int	is_good_piece(char *buf, size_t hashes, size_t contacts)
{
	size_t	i;

	i = 0;
	while (i < PIECE_READ - 1)								// Iterate buffer from first char of piece to the last char i == 19
	{
		if (i % 5 < 4 && (buf[i] != '#' && buf[i] != '.'))	// Check for illegal characters in first 4 chars per row
			return (error(BAD_PIECE_FORMAT));
		if (i % 5 == 4 && buf[i] != '\n')					// Check for illegal character at row separating newline's place
			return (error(BAD_PIECE_FORMAT));
		if (buf[i] == '#')									// If a hash # is found in current index of buffer
		{
			hashes++;										// Increment hash count
			contacts += count_contacts(&buf[i], i, 0);		// Get this piece's contact count
		}
		i++;
	}
	if (hashes != 4)										// Total hashes for a valid piece has to be 4
		return (error(BAD_HASH_COUNT));
	if (contacts != 6 && contacts != 8)						// Total contacts for a valid piece has to be 6 OR 8 (see description)
		return (error(BAD_PIECE_CONNECTION));
	return (i);												// Return non-negative to signify success.
}

/*
 *Checks for valid format of the pieces. Calls is_good_piece to determine
 *validity of a single piece, and increments i as the index of the first character
 *of the next piece in buffer. A check is done to see if the piece separating
 *newline is present. (&& i < ret makes sure that the previous piece wasn't the
 *last one, in which case there's no piece separator).
 */
static int	validate_pieces(char *buf, size_t ret)
{
	size_t	i;

	i = 0;
	while (i < ret)											// Iterate while index is not the count of returned characters (end of pieces)
	{
		if (is_good_piece(&buf[i], 0, 0) == -1)				// Check for every piece if it's a valid piece
			return (-1);
		i += PIECE_READ;									// Increment by 21 to get the index of the next piece's first character
		if (buf[i - 1] != '\n' && i < ret && i > 0)			// Check for newline separating pieces. If this is the last piece, no newline is needed.
			return (error(MISSING_NEWLINE));
	}
	return (0);												// Return 0 if every piece is valid and they're separated by a single newline.
}

/*
 * Read the input file into buffer and do various checks for it's validity.
 *
 * NOTE: because every piece (except the last one) is 20 bytes + the separating
 * newline, we can calculate the total number of pieces as (ret + 1) % 21.
 */
int	validate_file(const char *file, char *buf)
{
	int		fd;												// File descriptor for input file.
	ssize_t	ret;											// Read return value
	char	total_pieces;									// Count of pieces. Because every piece (except is 21

	fd = open(file, O_RDONLY);								// Open file for reading
	total_pieces = -1;										// REDUNDANT
	if (fd == -1)											// Check for open fail
		return (error(OPEN_FAIL));
	ret = read(fd, buf, MAX_READ + 1);						// Read to buffer
	if (ret < 0)											// Check for read fail
		return (error(READ_FAIL));
	if (close(fd) == -1)									// Close file and check for fail
		return (error(CLOSE_FAIL));
	buf[ret] = 0;											// Null terminate buffer
	if (ret > MAX_READ)										// Check if the file is longer than 26 (valid) pieces would be (26 is maximum)
		return (error(FILE_MAX));
	if ((ret + 1) % 21 != 0)								// Check if the amount of bytes read is valid (21 bytes per all other pieces than the last (-1))
		return (error(FILE_FORMAT));
	total_pieces = (ret + 1) / 21;							// Calculate amount of pieces
	if (validate_pieces(buf, ret) == -1)					// Validate all pieces to have correct format
		return (-1);
	return (total_pieces);									// Return number of pieces for main to store
}
