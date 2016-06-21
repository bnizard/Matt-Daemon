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

#ifndef DAEMON_HPP
# define DAEMON_HPP

# include "Matt_Daemon.hpp"

/*
** Classe du serveur daemon : initialisation, listen 4242, ecrire dans le logs.
*/

class Daemon
{
	public:
		// public attributes
		Logger				Log;
		Signal_handler		SigHandler;

		// public defaults Copplien
							Daemon( void );
							Daemon( Daemon const &src );
							~Daemon( void );
		Daemon 				&operator=( Daemon const &rhs );

		// public methods
		int					CreateServer(int port);
		int					Daemon_Main();

		int 				DaemonServer();
		int 				CreateDaemonProcess();
		bool    			isAlreadyRunning();
		void				EndOfDaemon();
};

#endif