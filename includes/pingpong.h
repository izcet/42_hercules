/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pingpong.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:33:04 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 17:01:43 by irhett           ###   ########.fr       */
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

typedef struct			srv_cli_info
{
	int					sockfd;
	pid_t				pid;
	int					br;
	char				buffer[BUFF_SIZE];
	struct sockaddr_in	cli_addr;
	unsigned int		cli_len;
	struct srv_cli_info	*next;
}						s_cli;

typedef struct			srv_info
{
	struct sockaddr_in	serv_addr;
	int					sockfd;
	struct srv_cli_info	*first;
}						s_srv;

int		open_inet_socket(void);
int		bind_local_socket(int s_fd, char *port, struct sockaddr_in *srv_adr);
int		connect_to_ip(char *ip, char *port, int sockfd);
int		init_sighandler(struct sigaction *action, void (*handle)(int));
s_srv	*init_serv_struct(char *port);
s_cli	*init_cli_struct(void);
int		client_connection(s_cli *cli, s_srv *srv);
void	close_clients(s_srv *srv);
int		connect_to_server(char *ip, char *port);

#endif
