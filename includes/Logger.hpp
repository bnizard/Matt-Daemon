/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 13:40:39 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/15 13:40:42 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

# include "Matt_Daemon.hpp"

class Logger
{
	public:
		std::ofstream		File;
		Tintin_reporter		Tintin;

		// Default Copplien methods
							Logger( void );
							Logger( Logger const &src );
							~Logger( void );
		Logger 				&operator=( Logger const &rhs );

		// My public methods.
		void				Init( void );
		
		void				AddLog(std::string Str);
		void				ClearLogFile();
		void				Created();
		void				Closed();
};

#endif
