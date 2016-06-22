/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cryptage.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 14:40:19 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/22 14:40:32 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRYPTAGE_HPP
# define CRYPTAGE_HPP

# include "Matt_Daemon.hpp"

/*
** Classe Cryptage : cryptage, decryptage.
*/

class Cryptage
{
	public:
		// public attributes
		int  PublicKey[2];
		int  PrivateKey[2];
		// public defaults Copplien
							Cryptage( void );
							Cryptage( Cryptage const &src );
							~Cryptage( void );
		Cryptage 			&operator=( Cryptage const &rhs );
							Cryptage( int* PublicKey, int* PrivateKey);

		// public methods
		std::string CryptMessage();
		std::string UnCryptMessage();
};

#endif
