/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cli_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 14:18:37 by irhett            #+#    #+#             */
/*   Updated: 2017/02/18 19:00:40 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pingpong.h"

s_cli	*init_cli_struct(void)
{
	s_cli	*client;

	client = (s_cli*)malloc(sizeof(s_cli));
	if (!client)
		error("initializing client structure.");
	ft_bzero(client, sizeof(*client));
	(*client).cli_len = sizeof((*client).cli_addr);
	(*client).next = NULL;
	return (client);
}
