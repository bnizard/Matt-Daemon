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
		// Public members
		bool				WithTimeStamp;

		// Default Public methods
							Tintin_reporter();
							Tintin_reporter( Tintin_reporter const &src );
							~Tintin_reporter();
		Tintin_reporter		&operator=( Tintin_reporter const &rhs );
						

		// My Public methods
		void				SetLogFile(std::string SelectedFilePath);
		void				UnsetLogFile();
		void				CreateNewLogFile(std::string str);
		void				DeleteLogFile(std::string FilePath);

		void				AddLogToFile(std::string SelectedFilePath,
														std::string Text);
		void				AddLog(std::string Str);

	private:
		time_t				timev;
		std::string			logFilePath;
		std::ofstream		logFileHandler;
		bool				islogFileSet;

		// My private methods
		void				PrintTimeStamp(std::ofstream *fileHandler);
};


#endif
