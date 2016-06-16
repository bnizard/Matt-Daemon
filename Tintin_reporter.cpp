/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tintin_reporter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 18:18:32 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/14 18:18:35 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matt_Daemon.hpp"

Tintin_reporter::Tintin_reporter() :	WithTimeStamp(true),logFile(NULL),
											logFileSet(false)
										
{

}

Tintin_reporter::~Tintin_reporter()
{

}

/*
** Set log file from existing file
*/
void Tintin_reporter::SetLogFile(std::ofstream *SelectedFile)
{
	if (this->logFileSet == false || logFile != NULL)
	{
		this->logFile = SelectedFile;
		this->logFileSet = true;
	}
	else
	{
		std::cout << "File already set for Tintin_reporter. Use UnsetLogFile() first.";
	}
}

void Tintin_reporter::UnsetLogFile()
{
	this->logFile = NULL;
	this->logFileSet = false;
}

void Tintin_reporter::CreateNewLogFile(std::string str)
{
	if (str[0])
	{}
}
/*
void Tintin_reporter::AddLogToFile(std::ofstream SelectedFile, std::string Text)
{
	if (WithTimeStamp)
	{
		PrintTimeStamp();
	}
	*SelectedFile << Text << "\n";
}

void Tintin_reporter::AddLog(std::string Text)
{
	if (this->logFileSet)
	{
		if (WithTimeStamp)
		{
			PrintTimeStamp(logFile);
		}
		SelectedFile << Text << "\n";
	}
	else
	{
		std::cout << "No file set for Tintin_reporter";
	}
}*/

void Tintin_reporter::PrintTimeStamp(std::ofstream *SelectedFile)
{
	//[ DD / MM / YYYY - HH : MM : SS ]
	time(&timev);
	if (SelectedFile)
	{}
	//SelectedFile << "timev to format\n";
}
