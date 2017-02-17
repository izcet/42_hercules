/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:40:45 by irhett            #+#    #+#             */
/*   Updated: 2017/02/16 22:47:14 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h> // for socket()
#include <sys/socket.h> // for socket()
#include <netinet/in.h> // for struct sockaddr_in

int		main(int argc, char **argv)
{
	char 				*buffer;
	struct sockaddr_in	serv_addr;
	struct sockaddr_in	cli_addr;
	int					sockfd;
	int					tempsockfd;
	int					port;
	unsigned int		cli_len;
	int					br;

	if (argc != 2)
	{
		ft_putendl("Usage: <application> <port>");
		return (0);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("Error opening socket.");

	ft_bzero((char*) &serv_addr, sizeof(serv_addr));
	port = ft_atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Error binding to socket.");
	listen(sockfd, 5);
	cli_len = sizeof(cli_addr);
	tempsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
	if (tempsockfd < 0)
		error("Error on accept.");
	while ((br = get_next_line(tempsockfd, &buffer)) > 0)
	{
		ft_putendl(buffer);
		free(buffer);
	}
	if (br < 0)
		error("Error reading from socket.");
	br = write(tempsockfd, "pong pong", ft_strlen("pong pong"));
	if (br < 0)
		error("Error writing to socket.");
	close(tempsockfd);
	close(sockfd);
	return (0);
}
