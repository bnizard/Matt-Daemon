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

void Cryptage::setPublicKey(char *PathToFile)
{
	char output[100];

	std::ifstream myReadFile;
 	myReadFile.open(PathToFile);
 
	if (myReadFile.is_open()) {
 		while (!myReadFile.eof()) {
			myReadFile >> output;
 		}
	}
	_PublicKey[0] = atoi(std::strtok(output, ";"));
	_PublicKey[1] = atoi(std::strtok(NULL, ";"));
	myReadFile.close();
}

void Cryptage::setPrivateKey(char *PathToFile)
{
	char output[100];

	std::ifstream myReadFile;
 	myReadFile.open(PathToFile);
 
	if (myReadFile.is_open()) {
 		while (!myReadFile.eof()) {
			myReadFile >> output;
 		}
	}
	_PrivateKey[0] = atoi(std::strtok(output, ";"));
	_PrivateKey[1] = atoi(std::strtok(NULL, ";"));
	myReadFile.close();
}

Cryptage::Cryptage(int* PubKey, int* PrivKey)
{
	_PublicKey[0] = PubKey[0];
	_PublicKey[1] = PubKey[1];
	_PrivateKey[0] = PrivKey[0];
	_PrivateKey[1] = PrivKey[1];
}


std::string Cryptage::CryptMessage(std::string message)
{
	std::string result;
	mpz_t res, val, exp, mod;
	char buf[1];

	mpz_init(res);
	mpz_init(val);
	mpz_init(exp);
	mpz_init(mod);
	for (std::string::size_type i = 0; i < message.length(); ++i)
	{
		sprintf(buf, "%d", (int)message[i]);
		mpz_set_str (val, buf, 10);
		mpz_set_str (exp, "7", 10);
		mpz_set_str (mod, "5141", 10);
		mpz_powm(res, val, exp, mod);
		result += mpz_get_str(NULL, 10, res);
		if (i < message.length() - 1)
    		result += " "; 	
	}
	return (result);
}

std::string Cryptage::UnCryptMessage(std::string message)
{
	std::string result;
	mpz_t res, val, exp, mod;
	std::list<char *> lst;
	char *s = NULL;
	char *token = NULL;

	mpz_init(res);
	mpz_init(val);
	mpz_init(exp);
	mpz_init(mod);

	s = (char*)message.c_str();
	token = std::strtok(s, " ");
	
	while (token != NULL)
	{
		lst.push_back(token);
		token = strtok(NULL, " ");
		if (!token)
			break;	
			
	}
	std::list<char*>::iterator p = lst.begin();
  	while (p != lst.end()) {
  		mpz_set_str (val, *p, 10);
		mpz_set_str (exp, "4279", 10);
		mpz_set_str (mod, "5141", 10);
		mpz_powm(res, val, exp, mod);
		result += (char)mpz_get_si(res);
   		p++;
  }
	return (result);
}