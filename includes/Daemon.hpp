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
		int					MaxClients; // set at 3 in default construct 

		// public defaults Copplien
							Daemon( void );
							Daemon( Daemon const &src );
							~Daemon( void );
		Daemon 				&operator=( Daemon const &rhs );

		// public methods
		int					CreateServer(int port);
		int					Daemon_Main();

		int					DaemonServer();
		int					ResetFdSet(int client_socket[3], int sock, fd_set *readfs);
		void				SearchForNewClients(int client_socket[3], int ret, int sock, fd_set *readfs);
		void				ReadOnClientSockets(int sock, int client_socket[3], fd_set *readfs);

		int					CreateDaemonProcess();
		bool				isAlreadyRunning();
		void				EndOfDaemon();

		// Setters
		void				SetEncryption(bool b);

		//utils
		std::string			to_string(int n);
	private:
		bool				_hasEncryption;
};

#endif