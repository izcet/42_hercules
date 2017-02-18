/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pingpong.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:33:04 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 00:04:36 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PINGPONG_H
#define PINGPONG_H

#include "libft.h"

#include <sys/types.h>		// for socket()
#include <sys/socket.h>		// for socket()
#include <netinet/in.h>		// for struct sockaddr_in
#include <stdio.h>			// for verbose printf() messages
#include <signal.h>			// for handling SIGTERM closure
#include <arpa/inet.h>		// for inet_aton() in client

int		open_inet_socket(void);
int		bind_local_socket(int s_fd, char *port, struct sockaddr_in *srv_adr);
int		connect_to_ip(char *ip, char *port, int sockfd);
int		init_sighandler(struct sigaction *action, void (*handle)(int));

#endif
