/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cryptage.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 14:40:11 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/22 14:40:15 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matt_Daemon.hpp"

Cryptage::Cryptage( void )
{

}

Cryptage::Cryptage( Cryptage const &src )
{
  *this = src;
}

Cryptage::~Cryptage( void )
{

}

Cryptage 			&Cryptage::operator=( Cryptage const &rhs )
{
	(void)rhs;
	return (*this);
}

Cryptage::Cryptage( int* PublicKey, int* PrivateKey)
{
	(void)PublicKey;
	(void)PrivateKey;
}


std::string Cryptage::CryptMessage()
{
	return (NULL);
}

std::string Cryptage::UnCryptMessage()
{
	return (NULL);
}
