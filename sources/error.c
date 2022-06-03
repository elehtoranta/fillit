/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:30:30 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/03 17:06:48 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

// Subject asks for 'error' on stdout, so this needs to be dumbed down
static void	print_error_message(int errorcode, const char **error_messages)
{
	ft_putstr("ERROR: ");
	ft_putendl_fd(error_messages[errorcode], 1);
}

// Returns -1 for caller to pass on
int	error(int errorcode)
{
	const char	*error_messages[ERROR_MESSAGES];

	error_messages[0] = "Number of arguments was not 1.";
	error_messages[1] = "Opening file failed.";
	error_messages[2] = "Reading file failed.";
	error_messages[3] = "File is too long.";
	error_messages[4] = "Bad file format, weird amount of characters.";
	error_messages[5] = "Bad file format, forbidden characters.";
	error_messages[6] = "Number of blocks (#) doesn't match.";
	error_messages[7] = "Closing file failed.";
	error_messages[8] = "Handled piece is invalid: bad connections.";
	print_error_message(errorcode, &error_messages[0]);
	return (-1);
}
