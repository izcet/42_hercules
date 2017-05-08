/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 18:40:45 by irhett            #+#    #+#             */
/*   Updated: 2017/05/07 21:28:27 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

volatile sig_atomic_t	done = 0;

static void				term(int signum)
{
	if (signum == SIGINT || signum == SIGTERM)
		ft_putendl("Closing server from external signal.");
	done = 1;
}

int						address_forwardable(char *s1, char *s2, char *s3)
{
	if (ft_strcmp(s1, "GET") != 0)
		return (0);
	if ((ft_strncmp(s3, "HTTP:/1.1", 8) == 0) || \
			(ft_strcmp(s3, "HTTP:/1.0", 8) == 0))
	{
		if (ft_strncmp(s2, "http://", 7) == 0)
			return (1);
	}
	return (0);
}

static void				forward_request(s_cli *tc)
{
	char	*s1;
	char	*s2;
	char	*s3;
	int		br;

	br = get_next_line(tc->sockfd, &s1);
	if (br < 0)
		ft_error("Unable to read from socket in child process.");
	br = get_next_line(tc->sockfd, &s2);
	if (br < 0)
		ft_error("Unable to read from socket in child process.");
	br = get_next_line(tc->sockfd, &s3);
	if (br < 0)
		ft_error("Unable to read from socket in child process.");
	if (address_forwardable(s1, s2, s3))
	{
		ft_putstr("Making request to: ");
		ft_putendl(s2);

	}
	else
		ft_error("Malformed request.");
}

static void				listen_to_client(s_srv *srv)
{
	pid_t	this_pid;
	s_cli	*tc;

	this_pid = fork();
	if (!this_pid)
	{
		tc = (*srv).first;
		forward_request(tc);
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
		listen((*srv).sockfd, CLI_QUEUE);
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
