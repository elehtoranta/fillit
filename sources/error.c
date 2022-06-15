/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:30:30 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/15 13:55:48 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#define ERROR_MESSAGES 12

// Subject asks for 'error' on stdout, so this needs to be dumbed down
static void	print_error_message(int errorcode, const char **error_messages)
{
	ft_putendl_fd(error_messages[errorcode], 1);
}

// Returns -1 for caller to pass on
int	error(int errorcode)
{
	const char	*error_messages[ERROR_MESSAGES];

	error_messages[0] = "usage: ./fillit <path/to/test/file>";
	error_messages[1] = "error";
	error_messages[2] = "error";
	error_messages[3] = "error";
	error_messages[4] = "error";
	error_messages[5] = "error";
	error_messages[6] = "error";
	error_messages[7] = "error";
	error_messages[8] = "error";
	error_messages[9] = "error";
	error_messages[10] = "error";
	error_messages[11] = "error";
	print_error_message(errorcode, &error_messages[0]);
	return (-1);
}
