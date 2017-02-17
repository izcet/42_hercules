/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:24:03 by irhett            #+#    #+#             */
/*   Updated: 2017/02/16 22:54:54 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int		main(int argc, char **argv)
{
	int					sockfd;
	int					port;
	int					br;
	struct sockaddr_in	serv_addr;
	struct addrinfo		hints;
	struct addrinfo		*res;
	char				*buffer;
	int					ret;

	if (argc != 3)
	{
		ft_putendl("Usage: client <host ip> <host port>");
		return (0);
	}
	port = ft_atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("Error opening socket.");
	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;
	ret = getaddrinfo(argv[1], argv[2], &hints, &res);
	if (ret != 0)
		error("Error finding host.");
	ft_bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	inet_aton(argv[1], (struct in_addr *) &serv_addr.sin_addr.s_addr);
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Error connecting.");
	while ((br = get_next_line(sockfd, &buffer)) > 0)
	{
		ret = write(sockfd, buffer, ft_strlen(buffer));
		free(buffer);
		if (ret < 0)
			error("Error writing to socket.");
	}
	if (br == -1)
		error("Error reading from STDIN.");
	while ((br = get_next_line(sockfd, &buffer)) > 0)
	{
		ft_putendl(buffer);
		free(buffer);
	}
	if (br == -1)
		error("Error reading from socket.");
	close(sockfd);
	return (0);
}
