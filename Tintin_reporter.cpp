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

Tintin_reporter::Tintin_reporter() :	WithTimeStamp(true), islogFileSet(false)
										
{

}

Tintin_reporter::~Tintin_reporter()
{
	// close file if file opened;
	if (islogFileSet)
	{
		logFileHandler.close();
		this->islogFileSet = false;
	}
}

/*
** Set log file from existing file
*/
void Tintin_reporter::SetLogFile(std::string SelectedFilePath)
{
	if (this->islogFileSet == false)
	{
		logFilePath = SelectedFilePath;
		this->islogFileSet = true;
	}
	else
	{
		std::cout << "File already set for Tintin_reporter. Use UnsetLogFile() first.\n";
	}
}

void Tintin_reporter::UnsetLogFile()
{
	this->islogFileSet = false;
}

/*
** Set log file from new file;
*/
void Tintin_reporter::CreateNewLogFile(std::string FilePath)
{
	if (this->islogFileSet == false)
	{
		logFileHandler.open(FilePath);
		logFilePath = FilePath;
		this->islogFileSet = true;
		logFileHandler.close();
	}
	else
	{
		std::cout << "File already set for Tintin_reporter. Use UnsetLogFile() first.\n";
	}
}

/*
** Add log to specified file;
*/
void Tintin_reporter::AddLogToFile(std::string SelectedFilePath, std::string Text)
{
	std::ofstream	CurFileStream;
	CurFileStream.open(SelectedFilePath);
	if (WithTimeStamp)
	{
		PrintTimeStamp(&CurFileStream);
	}
	CurFileStream << Text << "\n";
}

/*
** Add log to current set file;
*/
void Tintin_reporter::AddLog(std::string Text)
{
	if (this->islogFileSet == true)
	{
		logFileHandler.open(logFilePath);
		if (WithTimeStamp)
		{
			PrintTimeStamp(&logFileHandler);
		}
		logFileHandler << Text << "\n";
		logFileHandler.close();
	}
	else
	{
		std::cout << "No log file set for Tintin_reporter\n";
	}
}

void Tintin_reporter::PrintTimeStamp(std::ofstream *fileHandler)
{
	time(&timev);
	*fileHandler << "[timev to format DD / MM / YYYY - HH : MM : SS] ";
}
