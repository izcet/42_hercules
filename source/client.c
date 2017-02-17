/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:24:03 by irhett            #+#    #+#             */
/*   Updated: 2017/02/17 15:25:10 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

int		main(int argc, char **argv)
{
	int					sockfd;
	int					port;
	int					br;
	struct sockaddr_in	serv_addr;
	char				*buffer;
	int					ret;

	if (argc != 3)
	{
		printf("Usage: %s <host ip> <host port>", argv[0]);
		return (0);
	}
	
	port = ft_atoi(argv[2]);

	sockfd = open_inet_socket();
	if (sockfd < 0)
		error("Error opening socket.");
	
	ft_bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	inet_aton(argv[1], (struct in_addr *) &serv_addr.sin_addr.s_addr);
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Error connecting.");
	printf("connection made\n");
	
	while ((br = get_next_line(0, &buffer)) > 0)
	{
		ret = write(sockfd, buffer, ft_strlen(buffer));
		free(buffer);
		if (ret < 0)
			error("Error writing to socket.");
		ret = write(sockfd, "\0", 1);
		if (ret < 0)
			error("Error writing to socket.");
	}
	if (br == -1)
		error("Error reading from STDIN.");
	
	printf("transmission sent\n");
	
	while ((br = get_next_line(sockfd, &buffer)) > 0)
	{
		ft_putendl_fd(buffer, 1);
		free(buffer);
	}
	if (br == -1)
		error("Error reading from socket.");
	
	close(sockfd);
	return (0);
}
