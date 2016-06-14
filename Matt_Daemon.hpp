#ifndef MATT_DAEMON_HPP
# define MATT_DAEMON_HPP

#include <unistd.h>
#include <iostream>
#include <fstream>

# include <stdio.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/types.h>

class Tintin_reporter;
class Daemon;

# include "Daemon.hpp"
# include "Tintin_reporter.hpp"

#endif