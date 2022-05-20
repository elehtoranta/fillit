/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:27:13 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/20 18:20:30 by Erkka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"
#define MAX_VALID_FILE_SIZE 545
#define BUFF_SIZE 552

static void	handle_error(const char *error)
{
	putendl(error);
}

static int	check_file(int fd)
{
	char	buf[BUFF_SIZE];
	ssize_t	ret;

	ret = read(fd, buf, BUFF_SIZE);
	if (ret == -1)
		handle_error("Read operation failed with -1.");
	if (ret > MAX_VALID_FILE_SIZE)
		handle_error("ERROR: input file was too large.");
	return (0); //on success
}

int verify_file(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (!check_file())
		return (-1);

	return (0);
}
