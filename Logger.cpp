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

#include "Matt_Daemon.hpp"

Logger::Logger( void )
{
	Tintin.UnsetLogFile();
}

Logger::~Logger( void )
{

}

void Logger::Init( void )
{
	Tintin.CreateNewLogFile("test2.txt");
	Tintin.AddLog("Logger: Log file created.");
	// Correct path is "/var/log/matt_daemon/matt_daemon.log"
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