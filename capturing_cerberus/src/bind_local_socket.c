/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_local_socket.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:45:08 by irhett            #+#    #+#             */
/*   Updated: 2017/02/17 15:14:56 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

int		bind_local_socket(int s_fd, char *port, struct sockaddr_in *srv_adr)
{
	int		ret;

	ft_bzero((char*) srv_adr, sizeof(*srv_adr));
	(*srv_adr).sin_family = AF_INET;
	(*srv_adr).sin_port = htons(ft_atoi(port));
	(*srv_adr).sin_addr.s_addr = INADDR_ANY;
	ret = bind(s_fd, (struct sockaddr *) srv_adr, sizeof(*srv_adr));
	return (ret);
}
