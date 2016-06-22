
#ifndef CRYPTAGE_HPP
# define CRYPTAGE_HPP

# include "Matt_Daemon.hpp"

/*
** Classe Cryptage : cryptage, decryptage.
*/

class Cryptage
{
	public:
		// public defaults Copplien
							Cryptage( void );
							Cryptage( Cryptage const &src );
							~Cryptage( void );
		Cryptage 			&operator=( Cryptage const &rhs );
							Cryptage( int* PublicKey, int* PrivateKey);

		// public methods
		std::string CryptMessage(std::string message);
		std::string UnCryptMessage(std::string message);
	private:
			void	setPublicKey(char *PathToFile);
			void	setPrivateKey(char *PathToFile);

			int  	_PublicKey[2];
			int  	_PrivateKey[2];
};

#endif