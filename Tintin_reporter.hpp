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

#include "Matt_Daemon.hpp"

#ifndef TINTIN_REPORTER_HPP
#define TINTIN_REPORTER_HPP

/*
** Classe de journalisation du daemon. Creer le fichier et le lock. Ecrit dedans.
*/

class Tintin_reporter
{
	public:
		Tintin_reporter();
		~Tintin_reporter();
};


#endif