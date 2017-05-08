/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:52:00 by irhett            #+#    #+#             */
/*   Updated: 2017/02/15 17:29:59 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (s1 && s2)
	{
		while (((*s1 == *s2) && (*s1 != '\0')) && (n > 0) && (*s2 != '\0'))
		{
			s1++;
			s2++;
			n--;
		}
		if (n == 0)
			return (0);
		return ((unsigned char)(*s1) - (unsigned char)(*s2));
	}
	return (0);
}
