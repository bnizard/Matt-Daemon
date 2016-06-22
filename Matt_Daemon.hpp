#ifndef MATT_DAEMON_HPP
# define MATT_DAEMON_HPP

// General includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <iostream>
# include <sstream>
# include <fcntl.h>

// Journalisation
# include <fstream>
# include <cstring>

// Time format
# include <ctime>

//On inclut la bibliothèque gmp (Si gmpxx.h missing faire apt-get install libgmp-dev)
#include <gmpxx.h>

// Signals
# include <csignal>

// Server includes
# include <sys/socket.h>
# include <arpa/inet.h>
#include <netinet/in.h>
# include <netdb.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/select.h>
# include <errno.h>

// Class definitions

class Signal_handler;
class Tintin_reporter;
class Daemon;
class Logger;
class Cryptage;

// Class files includes
# include "Signal_handler.hpp"
# include "Tintin_reporter.hpp"
# include "Cryptage.hpp"
# include "Logger.hpp"
# include "Daemon.hpp"


#endif