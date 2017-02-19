/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:40:45 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 18:32:52 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

volatile sig_atomic_t	done = 0;

static void				term(int signum)
{
	if (signum == SIGINT)
		ft_putchar('\n');
	if (signum == SIGTERM)
		ft_putendl("Ouch! Why'd you have to stab me in the back?");
	done = 1;
}

static void				listen_to_client(s_srv *srv)
{
	pid_t	this_pid;
	s_cli	*tc;

	this_pid = fork();
	if (!this_pid)
	{
		tc = (*srv).first;
		(*tc).pid = this_pid;
		while (!done && (*tc).br >= 0)
		{
			while (((*tc).br = read((*tc).sockfd, (*tc).buffer, BUFF_SIZE)) > 0)
			{
				if (ft_strcmp((*tc).buffer, "ping") == 0)
					write((*tc).sockfd, "pong\npong\n", 10);
				else if (ft_strcmp((*tc).buffer, "fuck you") == 0)
				{
					write((*tc).sockfd, "No, Fuck you.\n", 14);
					close((*tc).sockfd);
					ft_putendl("Stopped talking to client, they were rude.");
					(*tc).sockfd = -1;
					(*tc).br = -1;
				}
				else
					write((*tc).sockfd, "I don't understand you.\n", 24);
			}
		}
		_exit(0);
	}
}

int						main(int argc, char **argv)
{
	s_srv				*srv;
	s_cli				*tmp_cli;
	struct sigaction	action;

	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		return (0);
	}
	srv = init_serv_struct(argv[1]);
	if (init_sighandler(&action, &term) != 0)
		error("initiating sigterm handler.");
	while (!done)
	{
		listen((*srv).sockfd, 5);
		tmp_cli = init_cli_struct();
		(*tmp_cli).sockfd = client_connection(tmp_cli, srv);
		if ((*tmp_cli).sockfd < 0)
			free(tmp_cli);
		else
		{
			ft_putendl("New client accepted.");
			(*tmp_cli).next = (*srv).first;
			(*srv).first = tmp_cli;
			listen_to_client(srv);
		}
	}
	close_clients(srv);	
	close((*srv).sockfd);
	free(srv);
	return (0);
}
