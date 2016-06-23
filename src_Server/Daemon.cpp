/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Daemon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 18:13:42 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/14 18:13:44 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Matt_Daemon.hpp"

Daemon::Daemon( void ) : MaxClients(3)
{
	char *s;

	s = (char *)malloc(50);
	getcwd(s, 100);
	_pwd = s;
	Log.Init();
	if (chdir("/var/lock/") == -1)
	{
		Log.AddLog((std::string)"[INFO] Server creating folder /var/lock");
		system("mkdir \"/var/lock\"");
	}
	Log.AddLog((std::string)"[INFO] Server creating file /var/lock/matt_daemon.lock");
	open("/var/lock/matt_daemon.lock", O_CREAT);
}

Daemon::Daemon( Daemon const &src )
{
	*this = src;
}

Daemon::~Daemon( void )
{
	EndOfDaemon();
}

Daemon 				&Daemon::operator=( Daemon const &rhs )
{
	Log = rhs.Log;
	SigHandler = rhs.SigHandler;
	return (*this);
}

void	Daemon::EndOfDaemon()
{
	int fd;
	int rc;

	fd = open("/var/lock/matt_daemon.lock", O_RDONLY);
	if ((rc = flock(fd, LOCK_UN) == 0))
	{
		Log.AddLog((std::string)"[INFO] Server removing /var/lock/matt_daemon.lock");
		remove ("/var/lock/matt_daemon.lock");
	}
	exit(0);
}

bool	Daemon::isAlreadyRunning()
{
	int fd;
	int rc;

	fd = open("/var/lock/matt_daemon.lock", O_RDONLY);
	if ((rc = flock(fd, LOCK_EX | LOCK_NB)))
		return false;
	return true;
}

int		Daemon::CreateServer(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		Log.AddLog("[ERROR] Server bind() error.");
		EndOfDaemon();
	}
	// Printing server infos
	printf("Port: %d\n", port);
	Log.AddLog((std::string)"[INFO] Server port: " + to_string(port));
	printf("Server socket: %d\n", sock);
	Log.AddLog((std::string)"[INFO] Server socket: " + to_string(sock));
	listen(sock, 3);
	printf("- Awaiting connections... -\n");
	Log.AddLog((std::string)"[INFO] Server - Awaiting connections... -");
	return (sock);
}

int		Daemon::Daemon_Main ()
{
	if (this->CreateDaemonProcess() != EXIT_SUCCESS
		|| this->DaemonServer() != EXIT_SUCCESS)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int 	Daemon::CreateDaemonProcess()
{
	pid_t				pid;

	if (getuid())
	{
		printf("%s", "You must be root!\n");
		Log.AddLog("[ERROR] 'Not as root' connection attempted.");
		EndOfDaemon();
	}

	if (!isAlreadyRunning())
	{
		printf("Process already running\n");
		Log.AddLog("[ERROR] Duplicate server start attempted. (process already running)");
		exit(-1);
	}
	// exit(0);
	// Fork the Parent Process
	pid = fork();

	if (pid < 0) {
		std::cout << "exit failure\n";
		exit(EXIT_FAILURE);
	}

	// We got a good pid, Close the Parent Process
	if (pid > 0) {
		std::cout << "exit success\n";
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int 	Daemon::DaemonServer()
{
	int					sock;
	int					client_socket[3];
	int 				max_sd;
	int					i;
	fd_set				readfs; 
	int					ret; // select ret
	Cryptage 			c;

	ret = 0;
	strcat(_pwd, "/src_Server/PrivateKey.key");
	c.setPrivateKey(_pwd);
	SigHandler.SetLog(&Log);
	SigHandler.SetDaemon(this);
	SigHandler.RegisterSignals();

	// Server initialization;
	sock = CreateServer(4242);
	Log.Created();
	
	// Initialise all client_socket[] to 0 so not checked
	for (i = 0; i < MaxClients; i++) 
	{
		client_socket[i] = 0;
	}

	// Client reception loop
	while (1)
	{
		// go reset the set of file descriptors for the select call;
		max_sd = ResetFdSet(client_socket, sock, &readfs);

		// Select call;
		if ((ret = select(max_sd + 1, &readfs, NULL, NULL, NULL)) < 0)
		{
			Log.AddLog("[ERROR] Select() Error. Quitting Server.");
			exit(-1);
		}

		// add new client if server sock has received any.
		SearchForNewClients(client_socket, ret, sock, &readfs);

		// go read on each client sockets.
		ReadOnClientSockets(sock, client_socket, &readfs, c);
	}
	close(sock);
	perror("Exit");
	return (EXIT_SUCCESS);
}

int Daemon::ResetFdSet(int client_socket[3], int sock, fd_set *readfs)
{
	int			i;
	int			sd;
	int			max_sd;

	max_sd = sock;
	// Clean set of fds.
	FD_ZERO(readfs);
	// Add server sock to set;
	FD_SET(sock, readfs);
	// Add child sockets to set
	for (i = 0 ; i < MaxClients ; i++)
	{
		//socket descriptor
		sd = client_socket[i];
		//if valid socket descriptor then add to read list
		if (sd > 0)
			FD_SET(sd , readfs);
		//highest file descriptor number, need it for the select function
		if (sd > max_sd)
			max_sd = sd;
	}
	return (max_sd);
}

void Daemon::SearchForNewClients(int client_socket[3], int ret, int sock, fd_set *readfs)
{
	int					i;
	int 				new_socket;
	struct sockaddr_in	csin;
	unsigned int		cslen = sizeof(csin);

	// Get new connections and add them to table
	if (FD_ISSET(sock, readfs) && ret > 0)
	{
		if ((new_socket = accept(sock, (struct sockaddr *)&csin, (socklen_t*)&cslen)) < 0)
		{
			perror("accept");
			Log.AddLog("[ERROR] Accept() Error. Quitting Server.");
			exit(EXIT_FAILURE);
		}
		i = 0;
		//for (i = 0; i < MaxClients; i++)
		while (i < MaxClients) // while is better to maintain counts.
		{
			// if socket position on server is empty
			if (client_socket[i] == 0 )
			{
				client_socket[i] = new_socket;
				printf("Adding to list of sockets as %d\n" , i);
				Log.AddLog((std::string)"[INFO] New client connected to server! Added to list of sockets as " + to_string(i));
				break;
			}
			i++;
		}
		// max client set
		if (i == MaxClients)
		{
			Log.AddLog((std::string)"[ERROR] New client attempted connection, but server has already reached maximum number of clients.");
		}
	}
}

void Daemon::ReadOnClientSockets(int sock, int client_socket[3], fd_set *readfs, Cryptage &c)
{
	int				i;
	char			buf_client[1000];
	int				sd;
	int				ret;
	char			*s = NULL;


	s = (char*)malloc(1000);
	(void)c;
	for (i = 0; i < MaxClients; i++) 
	{
		sd = client_socket[i];
		if (FD_ISSET(client_socket[i] , readfs))
		{
			ret = read(sd, buf_client, 1000 - 1);
			if (ret != 0)
			{
				buf_client[ret] = '\0';
				c.UnCryptMessage(buf_client, s);
				strcpy(buf_client, s);
				write(1, buf_client, strlen(buf_client));
				if (strcmp(buf_client, "quit\n") == 0)
				{
					Log.AddLog((std::string)"[INFO] Message from Client " + to_string(i) + " - \"" + (std::string)buf_client + "\"");
					Log.Closed();
					close(sock);
					EndOfDaemon();
				}
				Log.AddLog((std::string)"[INFO] Message from Client " + to_string(i) + " - \"" + (std::string)buf_client + "\"");
			} 
			else
			{
				// Client disconnected, clean socket;
				Log.AddLog((std::string)"[INFO] Client " + to_string(i) + " disconnected from server. Slot available on server.");
				client_socket[i] = 0;
			}
		}
	}
}

// Setters

void	Daemon::SetEncryption(bool b)
{
	this->_hasEncryption = b;
}

std::string Daemon::to_string(int n)
{
	std::ostringstream stm ;
	stm << n ;
	return stm.str() ;
}
