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

#include "Matt_Daemon.hpp"

Daemon::Daemon( void )
{
	if (chdir("/var/lock/") == -1)
		system("mkdir \"/var/lock\"");
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
		remove ("/var/lock/matt_daemon.lock");
	exit(0);
}

bool    Daemon::isAlreadyRunning()
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
	std::ofstream		outputFile;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		outputFile.open("Error.txt");
		outputFile << "error bind";
		outputFile.close();
		EndOfDaemon();
	}
	printf("Port: %d\n", port);
	printf("Server socket: %d\n", sock);
	listen(sock, 3);
	printf("- Awaiting connections... -\n");
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
 		EndOfDaemon();
 	}

	if (!isAlreadyRunning())
	{
		printf("Process already running\n");
		exit(-1);
	}
	// exit(0);
  	// Fork the Parent Process
    pid = fork();

    if (pid < 0) {
    	std::cout << "exit failure\n";
    	exit(EXIT_FAILURE);
    }

    //We got a good pid, Close the Parent Process
    if (pid > 0) {
    	std::cout << "exit success\n";
    	exit(EXIT_SUCCESS);
    }
    return (EXIT_SUCCESS);
}

int 	Daemon::DaemonServer()
{
 	int					sock;
 	int					client_sock;
 	char				buf_client[1000];

	unsigned int		cslen;
	struct sockaddr_in	*csin;
	int					ret; // pour le read.

	ret = 0;
    Log.Init();
    SigHandler.SetLog(&Log);
    SigHandler.SetDaemon(this);
    SigHandler.RegisterSignals();
    Log.Created();
	sock = CreateServer(4242);
	client_sock = accept(sock, (struct sockaddr *)&csin, &cslen);
	while ((ret = read(client_sock, buf_client, 1000 - 1)))
	{
		buf_client[ret] = '\0';
		printf("%s", buf_client);
		if (strcmp(buf_client, "quit\n") == 0)
		{
			Log.Closed();
			break;
		}
		Log.AddLog(buf_client);
	}
	return (EXIT_SUCCESS);
}
