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
	InitLogger();
}

Logger::~Logger( void )
{

}

void Logger::InitLogger( void )
{
	// Create file
	// File.open("/var/log/matt_daemon/matt_daemon.log");
	//Tintin = new Tintin_reporter();
	File.open("./testlogfile.log");
	Tintin.SetLogFile(&File);
}