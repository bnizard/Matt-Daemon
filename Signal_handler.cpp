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


Signal_handler *Signal_handler::instance = NULL;

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
	signal(SIGINT, Signal_handler::signalHandler);
	signal(SIGABRT, Signal_handler::signalHandler);
	signal(SIGFPE, Signal_handler::signalHandler);
	signal(SIGILL, Signal_handler::signalHandler);
	signal(SIGSEGV, Signal_handler::signalHandler);
	signal(SIGTERM, Signal_handler::signalHandler);
}

void		Signal_handler::signalHandler( int signum )
{
	std::stringstream LogString;
	if (instance->log != NULL)
	{
		LogString << "Received signal (" << signum << "). Quitting...";
		instance->log->AddLog(LogString.str());
		exit(signum);
	}
	else
	{
		std::cout << "No Logfile object set for Signal_Handler. Use SetLog().\n";
	}
	exit (signum);
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