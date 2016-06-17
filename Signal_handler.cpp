/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal_handler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 12:14:25 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/17 12:14:27 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Matt_Daemon.hpp"

Signal_handler *instance;

// signal() requires a static method. that's why I create an instance of the current
// signal handler object, to use it in the static method.
// Meaning, there must be only ONE object of signal_handler in the program.
Signal_handler::Signal_handler( void ) : log(NULL), daemon(NULL)
{
	instance = this;
}

Signal_handler::~Signal_handler( void )
{

}

void		Signal_handler::RegisterSignals()
{
	// Some might not be catchables ...
	std::signal(SIGABRT, signalHandler);
	std::signal(SIGINT, signalHandler);
	std::signal(SIGFPE, signalHandler);
	std::signal(SIGILL, signalHandler);
	std::signal(SIGSEGV, signalHandler);
	std::signal(SIGTERM, signalHandler);

}

void		Signal_handler::signalHandler( int signum )
{
	printf("sig call\n");
	std::stringstream LogString;
	if (instance->log != NULL)
	{
		LogString << "Received signal (" << signum << ").";
		instance->log->AddLog(LogString.str());
		if (instance->daemon != NULL)
		{
			//instance->daemon-> CLOSE SERVER CLEANLY METHOD ?.
			//exit(0);
		} else
			std::cout << "No Daemon object set for Signal_Handler. Use SetDaemon().\n";
	}
	else
	{
		std::cout << "No Logfile object set for Signal_Handler. Use SetLog().\n";
	}
}

// Setters
void		Signal_handler::SetLog(Logger *Nlog)
{
	this->log = Nlog;
}

void		Signal_handler::SetDaemon(Daemon *Ndaemon)
{
	this->daemon = Ndaemon;
}