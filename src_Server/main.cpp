/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 18:11:36 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/14 18:11:45 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Matt_Daemon.hpp"

int main (int argc, char **argv)
{
	Daemon d;
	
	d.SetEncryption(true);
	if (argc > 1)
	{
		if ((strcmp(argv[1], "-c") == 0)  && argc == 2)
		{
			d.Log.AddLog("[INFO] Launch without Decrypt message mode");
			d.SetEncryption(false);
		}
		else
		{
			printf("Usage: ./Matt_Daemon [-u]\n");
			return (-1);
		}
	}
	return (d.Daemon_Main());
}
