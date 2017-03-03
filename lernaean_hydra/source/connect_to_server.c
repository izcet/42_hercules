/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_to_server.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:49:13 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 16:53:33 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

int		connect_to_server(char *ip, char *port)
{
	int		sockfd;

	sockfd = open_inet_socket();
	if (sockfd < 0)
		error("opening socket.");
	if (connect_to_ip(ip, port, sockfd) < 0)
		error("connecting to server.");
	ft_putendl("Connected to server.");
	return (sockfd);
}
