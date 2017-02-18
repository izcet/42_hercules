/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:40:45 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 01:17:07 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

volatile sig_atomic_t	done = 0;

void					term(int signum)
{
	if (signum == SIGTERM)
		ft_putendl("Process killed by SIGTERM");
	if (signum == SIGINT)
		ft_putendl("Process killed by SIGINT");
	done = 1;
}

int						main(int argc, char **argv)
{
	char 				buffer[BUFF_SIZE];
	struct sockaddr_in	serv_addr;
	struct sockaddr_in	cli_addr;
	unsigned int		cli_len;
	int					sockfd;
	int					tempsockfd;
	int					br;
	struct sigaction	action;

	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		return (0);
	}

	sockfd = open_inet_socket(); 
	if (sockfd < 0)
		error("opening socket.");

	if (bind_local_socket(sockfd, argv[1], &serv_addr) < 0)
		error("binding to socket.");

	if (init_sighandler(&action, &term) != 0)
		error("initiating sigterm handler.");
	while (!done)
	{
		/*printf("%i\n", i);
		  int t = sleep(3);
		  while (t > 0)
		  {
		  printf("Fuck you I'm invincible. \nYou can't kill me, I'm...\n");
		  int x = 0;
		  while (x < 16)
		  {
		  printf("Na\n");
		  x++;
		  }
		  printf("BATMAN, motherfucker\n");
		  t = sleep(t);
		  }
		  i++;
		  if (i > 300)
		  i = 0;*/
		printf("listen is %i\n", listen(sockfd, 5));
		cli_len = sizeof(cli_addr);
		tempsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
		if (tempsockfd < 0)
			error("on accept.");
		printf("Client accepted.\n");
		br = 0;
		while (br >= 0)
		{
			ft_bzero(&buffer, BUFF_SIZE);
			br = read(tempsockfd, buffer, BUFF_SIZE);
			if (br)
			{
				printf("Line read:\n");
				write(1, buffer, br);
				write(tempsockfd, buffer, br);
				write(1, "\n", 1);
			}
		}
		if (br < 0)
			error("reading from socket.");

		printf("Done reading.\n");	
		br = write(tempsockfd, "pong pong", ft_strlen("pong pong"));
		if (br < 0)
			error("writing to socket.");

		close(tempsockfd);

	}
	close(sockfd);
	return (0);
}
