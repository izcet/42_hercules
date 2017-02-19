/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:24:03 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 13:06:13 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

int		main(int argc, char **argv)
{
	int					sockfd;
	int					br;
	char				*buffer;
	int					ret;

	if (argc != 3)
	{
		printf("Usage: %s <host ip> <host port>", argv[0]);
		return (0);
	}
	
	sockfd = open_inet_socket();
	if (sockfd < 0)
		error("Error opening socket.");
	
	if (connect_to_ip(argv[1], argv[2], sockfd) < 0)
		error("Error connecting.");
	printf("Connection made to %s port %s\n\n", argv[1], argv[2]);
	
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
