/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 21:24:03 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 18:09:38 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"
#include <fcntl.h>		// for non_blocking
#include <errno.h>

volatile sig_atomic_t	done = 0;

static void				term(int signum)
{
	if (signum == SIGINT)
		ft_putchar('\n');
	if (signum == SIGTERM)
		ft_putendl("Ouch! That hurt!");
	done = 1;
}

int						main(int argc, char **argv)
{
	int					sockfd;
	int					br;
	char				*user_mess;
	char				serv_mess[BUFF_SIZE];
	struct sigaction	action;
	if (argc != 3)
	{
		printf("Usage: %s <host ip> <host port>", argv[0]);
		return (0);
	}

//	int flags;
	sockfd = connect_to_server(argv[1], argv[2]);
/*	if ((flags = fcntl(sockfd, F_GETFL, 0)) < 0)
		error("setting non-blocking 1");
	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0)
		error("setting non-blocking 2");
*/
	if (init_sighandler(&action, &term) != 0)
		error("initiating sigterm handler.");
	while (!done)
	{
		ft_putendl("Enter input to send:");
		br = get_next_line(0, &user_mess);
		if (br < 0)
			ft_putendl("Error reading from STDIN.");
		else
		{
			br = write(sockfd, user_mess, ft_strlen(user_mess));
			free(user_mess);
			if (br < 0)
			{
				ft_putendl("Error writing to socket.");
				done = 1;
			}
		}
		ft_putendl("Done sending. Receiving:");
		br = 1;
		sleep(1);
		while ((br >= 0) && (!done))
		{
			ft_bzero(&serv_mess, BUFF_SIZE);
			br = read(sockfd, serv_mess, BUFF_SIZE);
			if (br > 0)
				write(1, serv_mess, br);
			else
			{
				printf("Errno is %i\n", errno);
				if (errno != EWOULDBLOCK)
				{
					ft_putendl("Error reading from socket.");
					done = 1;
				}
			}
		}
		ft_putendl("Done receiving.");
	}
	ft_putendl("Disconnecting from server.");	
	close(sockfd);
	return (0);
}
