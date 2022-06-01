/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:21:53 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/01 20:30:56 by Erkka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	static t_piece	pieces[MAX_PIECES];
	/*static t_board	board;*/

	if (argc != 2)
		return (error(BAD_ARGS));
	if (extract_file(argv[1], &pieces[0]) == -1)
		return (-1);
	/*
	 *if (teardown() == -1)
	 *    return (-1);
	 */
	return (0);
}
