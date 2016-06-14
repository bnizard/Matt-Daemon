/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Daemon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 18:14:00 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/14 18:14:05 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matt_Daemon.hpp"

#ifndef MATT_DAEMON_HPP
#define MATT_DAEMON_HPP

/*
** Classe du serveur daemon : initialisation, listen 4242, ecrire dans le logs.
*/

class Daemon
{
	public:
		Daemon( void );
		~Daemon( void );

		//Tintin_reporter		Journal;
		int		create_server(int port);
		int		main_test();


};


#endif