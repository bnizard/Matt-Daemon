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
											islogFileSet(false)
										
{

}

Tintin_reporter::~Tintin_reporter()
{
	// close file if file opened;
	if (islogFileSet)
	{
		(*this->logFile).close();
		this->islogFileSet = false;
	}
}

/*
** Set log file from existing file
*/
void Tintin_reporter::SetLogFile(std::ofstream *SelectedFile)
{
	if (this->islogFileSet == false && logFile != NULL)
	{
		this->logFile = SelectedFile;
		this->islogFileSet = true;
	}
	else
	{
		std::cout << "File already set for Tintin_reporter. Use UnsetLogFile() first.";
	}
}

void Tintin_reporter::UnsetLogFile()
{
	this->logFile = NULL;
	if (this->logFile)
	{
		(*this->logFile).close();
	}
	this->islogFileSet = false;
}

/*
** Set log file from new file;
*/
void Tintin_reporter::CreateNewLogFile(std::string FilePath)
{
	if (this->islogFileSet == false && logFile != NULL)
	{
		std::ofstream	NewFile;

		NewFile.open(FilePath);
		SetLogFile(&NewFile);
	}
	else
	{
		std::cout << "File already set for Tintin_reporter. Use UnsetLogFile() first.";
	}
}

/*
** Add log to specified file;
*/
void Tintin_reporter::AddLogToFile(std::ofstream *SelectedFile, std::string Text)
{
	if (WithTimeStamp)
	{
		PrintTimeStamp(logFile);
	}
	*SelectedFile << Text << "\n";
}

/*
** Add log to current set file;
*/
void Tintin_reporter::AddLog(std::string Text)
{
	if (this->islogFileSet == true && this->logFile != NULL)
	{
		if (WithTimeStamp)
		{
			PrintTimeStamp(logFile);
		}
		*logFile << Text << "\n";
	}
	else
	{
		std::cout << "No log file set for Tintin_reporter";
	}
}

void Tintin_reporter::PrintTimeStamp(std::ofstream *SelectedFile)
{
	//[ DD / MM / YYYY - HH : MM : SS ]
	time(&timev);
	*SelectedFile << "[timev to format DD / MM / YYYY - HH : MM : SS] ";
}
