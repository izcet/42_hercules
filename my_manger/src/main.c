/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 23:29:04 by irhett            #+#    #+#             */
/*   Updated: 2017/04/07 21:14:56 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

volatile sig_atomic_t	done = 0;

static void				term(int signum)
{
	if (signum == SIGINT)
		ft_putendl("Don't interrupt me, I'm speaking.");
	if (signum == SIGTERM)
		ft_putendl("Ouch! Why'd you have to stab me in the back?");
	if (signum == SIGHUP)
		ft_putendl("go hang yourself");
	if (signum == SIGQUIT)
		ft_putendl("I'm never going to quit!");
	if (signum == SIGABRT)
		ft_putendl("Mission cannot be aborted.");
	if (signum == SIGALRM)
		ft_putendl("Ring ring, it's the depression.");
	if (signum == SIGKILL)
		ft_putendl("I'm gonna catch it!");
	done = 0;
}

void	print(int x)
{
	char *str;
	str = ft_itoa(x);
	ft_putendl(str);
	free(str);
}

int		init_sighandler(struct sigaction *action, void (*handle)(int))
{
	int		ret;

	ret = 0;
	ft_bzero(action, sizeof(*action));
	(*action).sa_handler = *handle;
	ret += sigaction(SIGINT, action, NULL);
	ret += sigaction(SIGTERM, action, NULL);
	ret += sigaction(SIGHUP, action, NULL);
	ret += sigaction(SIGQUIT, action, NULL);
	ret += sigaction(SIGABRT, action, NULL);
	ret += sigaction(SIGALRM, action, NULL);
	return (ret);
}

int						main(int argc, char **argv)
{
	struct sigaction	action;
	int					pid;

	if (init_sighandler(&action, &term) != 0)
		error("initiating sigterm handler.");
	while (!done)
	{
		pid = fork();
		if	(pid)
			ft_putendl("Oops I had a kid.");
		sleep(5);
	}
	(void)argc;
	(void)argv;
	return (0);
}
