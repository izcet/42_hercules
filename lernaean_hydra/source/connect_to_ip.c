/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_to_ip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:27:27 by irhett            #+#    #+#             */
/*   Updated: 2017/02/17 15:33:10 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

int		connect_to_ip(char *ip, char *port, int sockfd)
{
	struct	sockaddr_in		serv_addr;
	int						ret;

	ft_bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_UNSPEC;
	serv_addr.sin_port = htons(ft_atoi(port));
	inet_aton(ip, (struct in_addr *) &serv_addr.sin_addr.s_addr);
	ret = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	return (ret);
}
