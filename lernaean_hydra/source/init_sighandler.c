/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sighandler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 23:29:04 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 00:22:35 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

int		init_sighandler(struct sigaction *action, void (*handle)(int))
{
	int		ret;

	ret = 0;
	ft_bzero(action, sizeof(*action));
	(*action).sa_handler = *handle;
	ret += sigaction(SIGINT, action, NULL);
	ret += sigaction(SIGTERM, action, NULL);
	return (ret);
}
