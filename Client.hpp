/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 15:36:18 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/22 15:36:21 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Matt_Daemon.hpp"

class Client
{
	public:
		// Public vars
		int		sock;
		int		port;

		// Default Copplien methods
							Client( void );
							Client( Client const &src );
							~Client( void );
		Client 				&operator=( Client const &rhs );

		// My public methods.
		void				usage();
		int					check_arg1(char *arg);
		int					check_args_client(int port);
		int					create_client(char *addr, int port);
		void				prompt(void);
		void				client_prompt(int sock);
};

#endif
