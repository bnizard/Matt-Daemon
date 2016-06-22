/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 14:39:46 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/22 14:39:59 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matt_Daemon.hpp"

int main(int argc, char **argv)
{
	Client		Cl;

	if (argc != 3)
		Cl.usage();
	else
	{
		Cl.port = atoi(argv[2]);
		if (Cl.check_args_client(Cl.port) != 0)
			return (-1);
		Cl.sock = Cl.create_client(argv[1], Cl.port);
		Cl.client_prompt(Cl.sock);
		close(Cl.sock);
	}
	return (0);
}
