/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_serv_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 01:39:29 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 14:02:31 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

s_srv	*init_serv_struct(char *port)
{
	s_srv	*server;

	server = (s_srv*)malloc(sizeof(s_srv));
	if (!server)
		error("allocating space for server structure.");
	ft_bzero(server, sizeof(*server));
	(*server).sockfd = open_inet_socket();
	if ((*server).sockfd < 0)
	{
		free(server);
		error("opening socket.");
	}
	if (bind_local_socket((*server).sockfd, port, &(*server).serv_addr) < 0)
	{
		close((*server).sockfd);
		free(server);
		error("binding to socket. (already in use?)");
	}
	printf("Server initialized and bound to port %s.\n", port);
	return (server);
}
