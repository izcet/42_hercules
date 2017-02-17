/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:40:45 by irhett            #+#    #+#             */
/*   Updated: 2017/02/17 15:15:50 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

int		main(int argc, char **argv)
{
	char 				*buffer;
	struct sockaddr_in	serv_addr;
	struct sockaddr_in	cli_addr;
	unsigned int		cli_len;
	int					sockfd;
	int					tempsockfd;
	int					br;

	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		return (0);
	}

	sockfd = open_inet_socket(); 
	if (sockfd < 0)
		error("Error opening socket.");

	if (bind_local_socket(sockfd, argv[1], &serv_addr) < 0)
		error("Error binding to socket.");

	listen(sockfd, 5);
	cli_len = sizeof(cli_addr);
	tempsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
	if (tempsockfd < 0)
		error("Error on accept.");
	printf("Client accepted.\n");

	while ((br = get_next_line(tempsockfd, &buffer)) > 0)
	{
		printf("Line read:\n");
		ft_putendl_fd(buffer, 1);
		free(buffer);
	}
	if (br < 0)
		error("Error reading from socket.");

	printf("Done reading.\n");	
	br = write(tempsockfd, "pong pong", ft_strlen("pong pong"));
	if (br < 0)
		error("Error writing to socket.");

	close(tempsockfd);
	close(sockfd);
	return (0);
}
