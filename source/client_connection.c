/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_connection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 14:30:26 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 15:00:24 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

int		client_connection(s_cli *c, s_srv *srv)
{
	int		ret;
	int		sock;
	
	sock = (*srv).sockfd;
	ret = accept(sock, (struct sockaddr *) &((*c).cli_addr), &((*c).cli_len));
	return (ret);
}
