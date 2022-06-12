/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:02:02 by elehtora          #+#    #+#             */
/*   Updated: 2022/06/10 17:06:11 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdint.h>
//Defines for utils functions
void	print_board(uint16_t *board);
void	gui_hex(uint64_t piece);
void	print_piece_r2l(uint16_t piece);
void	print_piece_l2r(uint16_t piece);

#endif
