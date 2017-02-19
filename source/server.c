/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:40:45 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 16:06:13 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

volatile sig_atomic_t	done = 0;

void					term(int signum)
{
	ft_putendl("");
	if (signum == SIGTERM)
		printf("Process killed by SIGTERM\n");
	if (signum == SIGINT)
		printf("Process killed by SIGINT\n");
	done = 1;
}

void					listen_to_client(s_srv *srv)
{
	pid_t	this_pid;
	s_cli	*tc;

	this_pid = fork();
	if (this_pid)
	{
		printf("PID of fork is %i\n", this_pid);
		tc = (*srv).first;
		(*tc).pid = this_pid;
		while (!done && (*tc).br >= 0)
		{
			while (((*tc).br = read((*tc).sockfd, (*tc).buffer, BUFF_SIZE)) > 0)
			{
				if (ft_strcmp((*tc).buffer, "ping") == 0)
					write((*tc).sockfd, "pong\npong\n", 10);
				if (ft_strcmp((*tc).buffer, "fuck you") == 0)
				{
					write((*tc).sockfd, "No, Fuck you.\n", 14);
					close((*tc).sockfd);
					(*tc).sockfd = -1;
					(*tc).br = -1;
				}
			}
		}
		exit(0);
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
		int t = sleep(1);
		while (t > 0)
		{
			//this block enters when a kill is recieved or done is not 0
			t = sleep(t);
		}

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
