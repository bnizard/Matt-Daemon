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

		//static Signal_handler	*instance;
		// Default Public methods
								Signal_handler( void );
								~Signal_handler( void );

		void					RegisterSignals();

		// Setters
		void					SetLog(Logger *Nlog);
		void					SetDaemon(Daemon *Ndaemon);

		static void				signalHandler( int signum );

	private:
		Logger					*log;
		Daemon					*daemon;
	
};


extern Signal_handler *instance;

#endif