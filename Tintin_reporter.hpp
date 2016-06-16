/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tintin_reporter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 18:18:39 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/14 18:18:41 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef TINTIN_REPORTER_HPP
# define TINTIN_REPORTER_HPP

# include "Matt_Daemon.hpp"

/*
** Classe de journalisation. Ecrit et lock le fichier.
*/

class Tintin_reporter
{
	public:
		bool			WithTimeStamp;

						Tintin_reporter();
						~Tintin_reporter();

		void			SetLogFile(std::ofstream *SelectedFile);
		void			UnsetLogFile();
		void			CreateNewLogFile(std::string str);

		//void AddLogToFile(std::ofstream SelectedFile, std::string Str);
		//void AddLog(std::string Str);

	private:
		time_t			timev;
		std::ofstream	*logFile;
		bool			logFileSet;

		void			PrintTimeStamp(std::ofstream *SelectedFile);
};


#endif
