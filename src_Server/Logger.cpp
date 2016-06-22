/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 13:40:10 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/15 13:40:33 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Matt_Daemon.hpp"

// Init() is done after the server fork, that's why it's not used here.
Logger::Logger( void )
{
	Tintin.UnsetLogFile();
}

Logger::Logger(Logger const &src)
{
	*this = src;
}

Logger::~Logger( void )
{

}

Logger		&Logger::operator=(Logger const & rhs)
{
	(void)rhs;
	return (*this);
}

void Logger::Init( void )
{
	if (chdir("/var/log/matt_daemon") == -1)
		system("mkdir \"/var/log/matt_daemon\"");
	open("/var/log/matt_daemon/matt_daemon.log", O_CREAT | O_APPEND);

	Tintin.CreateNewLogFile("/var/log/matt_daemon/matt_daemon.log");
	Tintin.AddLog("Logger: Log file created.");
}

void Logger::AddLog(std::string Str)
{
	Tintin.AddLog(Str);
}

void Logger::Created()
{
	Tintin.AddLog("Matt_Daemon Created.");
}

void Logger::Closed()
{
	Tintin.AddLog("Matt_Daemon Closed.");
}
