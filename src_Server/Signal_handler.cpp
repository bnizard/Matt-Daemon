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


#include "../includes/Matt_Daemon.hpp"


Signal_handler *Signal_handler::instance = NULL;

// signal() requires a static method. that's why I create an instance of the current
// signal handler object, to use it in the static method.
// Meaning, there must be only ONE object of signal_handler in the program.
Signal_handler::Signal_handler( void ) : log(NULL), daemon(NULL)
{
	instance = this;
}

Signal_handler::Signal_handler(Signal_handler const &src){
	*this = src;
}

Signal_handler::~Signal_handler( void )
{

}

Signal_handler &	Signal_handler::operator=(Signal_handler const & rhs)
{
	log = rhs.log;
	daemon = rhs.daemon;
	instance = this;
	return (*this);
}

void		Signal_handler::RegisterSignals()
{
	signal(SIGHUP, Signal_handler::signalHandler); // 12
	signal(SIGINT, Signal_handler::signalHandler); // 2
	signal(SIGQUIT, Signal_handler::signalHandler); // 3
	signal(SIGILL, Signal_handler::signalHandler); // 4
	signal(SIGTRAP, Signal_handler::signalHandler); // 5
	signal(SIGABRT, Signal_handler::signalHandler); // 6
	signal(7, Signal_handler::signalHandler); // 7 undefined
	signal(SIGFPE, Signal_handler::signalHandler); // 8
	//signal(SIGKILL, Signal_handler::signalHandler); // 9 cant be caught
	signal(SIGBUS, Signal_handler::signalHandler); // 10
	signal(SIGSEGV, Signal_handler::signalHandler); // 11
	signal(SIGSYS, Signal_handler::signalHandler); // 12
	signal(SIGPIPE, Signal_handler::signalHandler); // 13
	signal(SIGALRM, Signal_handler::signalHandler); // 14
	signal(SIGTERM, Signal_handler::signalHandler); // 15
	signal(SIGURG, Signal_handler::signalHandler); // 16
	//signal(SIGSTOP, Signal_handler::signalHandler); // 17 cant be caught
	signal(SIGTSTP, Signal_handler::signalHandler); // 18
	signal(SIGCONT, Signal_handler::signalHandler); // 19
	signal(SIGCHLD, Signal_handler::signalHandler); // 20
	signal(SIGTTIN, Signal_handler::signalHandler); // 21
	signal(SIGTTOU, Signal_handler::signalHandler); // 22
	signal(SIGIO, Signal_handler::signalHandler); // 23
	signal(SIGXCPU, Signal_handler::signalHandler); // 24
	signal(SIGXFSZ, Signal_handler::signalHandler); // 25
	signal(SIGVTALRM, Signal_handler::signalHandler); // 26
	signal(SIGPROF, Signal_handler::signalHandler); // 27
	signal(SIGWINCH, Signal_handler::signalHandler); // 28
	signal(29, Signal_handler::signalHandler); // 29 undefined
	signal(SIGUSR1, Signal_handler::signalHandler); // 30
	signal(SIGUSR2, Signal_handler::signalHandler); // 31
}

void		Signal_handler::signalHandler( int signum )
{
	std::stringstream LogString;
	if (instance->log != NULL)
	{
		LogString << "[INFO] Received signal (" << signum << "). Quitting...";
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