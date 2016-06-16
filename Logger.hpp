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

		// Default Public methods
				Logger( void );
				~Logger( void );
				// Copplien ....

		void	InitLogger( void );

		// My public methods.
		void	AddLog(std::string Str);
		void	Created();
		void	Closed();
};

#endif
