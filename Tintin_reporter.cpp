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

Tintin_reporter::Tintin_reporter( Tintin_reporter const &src )
{
	*this = src;
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

Tintin_reporter		&Tintin_reporter::operator=( Tintin_reporter const &rhs )
{
	islogFileSet = rhs.islogFileSet;
	logFilePath = rhs.logFilePath;
	return (*this);
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
	char *Str = new char[FilePath.length() + 1];
	std::strcpy(Str, FilePath.c_str());

	if (this->islogFileSet == false)
	{
		logFileHandler.open(Str);
		logFilePath = FilePath;
		this->islogFileSet = true;
		logFileHandler.close();
	}
	else
	{
		std::cout << "File already set for Tintin_reporter. Use UnsetLogFile() first.\n";
	}
	delete[] Str;
}

/*
** Add log to specified file;
*/
void Tintin_reporter::AddLogToFile(std::string SelectedFilePath, std::string Text)
{
	std::ofstream	CurFileStream;
	char *Str = new char[SelectedFilePath.length() + 1];
	std::strcpy(Str, SelectedFilePath.c_str());

	CurFileStream.open(Str, std::fstream::app);
	if (WithTimeStamp)
	{
		PrintTimeStamp(&CurFileStream);
	}
	CurFileStream << Text << "\n";
	delete[] Str;
}

/*
** Add log to current set file;
*/
void Tintin_reporter::AddLog(std::string Text)
{
	char *Str = new char[logFilePath.length() + 1];
	std::strcpy(Str, logFilePath.c_str());
	
	if (this->islogFileSet == true)
	{
		logFileHandler.open(Str, std::fstream::app);
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
	char		formattedOutput[34];
	struct tm	*timeInfo;

	formattedOutput[33] = '\0';
	time(&timev);
	timeInfo = localtime(&timev);
	strftime (formattedOutput, 34, "[%d/%m/%Y-%H:%M:%S] ", timeInfo);
	*fileHandler << formattedOutput;
}
