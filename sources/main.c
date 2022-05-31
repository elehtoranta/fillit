/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:21:53 by elehtora          #+#    #+#             */
/*   Updated: 2022/05/30 12:41:50 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"



int	main(int argc, char **argv)
{
	char	*file;

	if (argc != 2)
		return (error(BAD_ARGS));
	file = argv[1];
	if (verify_file(file) == -1)
		return (-1);
	if (teardown() == -1)
		return (-1);
	return (0);
}
