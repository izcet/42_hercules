/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_inet_socket.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:42:05 by irhett            #+#    #+#             */
/*   Updated: 2017/02/17 14:58:15 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

int		open_inet_socket(void)
{
	int		sockfd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	return (sockfd);
}
