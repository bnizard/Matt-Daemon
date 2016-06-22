/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal_handler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 12:14:31 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/17 12:14:32 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIGNAL_HANDLER_HPP
# define SIGNAL_HANDLER_HPP

# include "Matt_Daemon.hpp"

class Signal_handler
{
	public:
		// static singleton variable.
		static Signal_handler	*instance;
								// Copplien form methods
								Signal_handler( void );
								Signal_handler( Signal_handler const &src );
								~Signal_handler( void );
		Signal_handler 			&operator=( Signal_handler const &rhs );

		// My methods
		void					RegisterSignals();
		// Setters
		void					SetLog(Logger *Nlog);
		void					SetDaemon(Daemon *Ndaemon);

		static void				signalHandler( int signum );

	private:
		Logger					*log;
		Daemon					*daemon;
	
};


#endif