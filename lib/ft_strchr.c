/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:59:59 by elehtora          #+#    #+#             */
/*   Updated: 2022/02/24 23:34:51 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	while (*((char *) s) && *((char *) s) != (char) c)
		s++;
	if (*((char *) s) == (char) c)
		return ((char *) s);
	return (NULL);
}
