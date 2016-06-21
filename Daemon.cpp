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
	int					client_socket[3];
	int 				max_clients = 3;
	int 				max_sd;
	int 				new_socket;
	int 				sd;
	char				buf_client[1000];
	int i;

	struct sockaddr_in	csin;
	unsigned int		cslen = sizeof(csin);
	int					ret; // pour le read.

// select implementation
	fd_set				readfs;

	i = 0;
	ret = 0;
	Log.Init();
	SigHandler.SetLog(&Log);
	SigHandler.SetDaemon(this);
	SigHandler.RegisterSignals();
	sock = CreateServer(4242);
	Log.Created();

	//initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) 
    {
        client_socket[i] = 0;
    }

	// Client reception loop
	while (1)
	{
		FD_ZERO(&readfs);
		FD_SET(sock, &readfs);
		max_sd = sock;

		 // add child sockets to set
        for ( i = 0 ; i < max_clients ; i++) 
        {
            //socket descriptor
            sd = client_socket[i];
            //if valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET( sd , &readfs);
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

		//ft_sock_reception(client_sock);
		if ((ret = select(max_sd + 1, &readfs, NULL, NULL, NULL)) < 0)
		{
			exit(-1);
		}

		// Get new connections and add them to table
		if (FD_ISSET(sock, &readfs) && ret > 0)
		{
			printf("toto\n");
			if ((new_socket = accept(sock, (struct sockaddr *)&csin, (socklen_t*)&cslen)) < 0)
            {
            	perror("accept");
                exit(EXIT_FAILURE);
            }
			for (i = 0; i < max_clients; i++) 
            {
                //if position is empty
                if (client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);
                     
                    break;
                }
            }
            // close(new_socket);
		}
		
		// read on clients.
        for (i = 0; i < max_clients; i++) 
    	{
    		sd = client_socket[i];
            if (FD_ISSET(client_socket[i] , &readfs))
			{
				//client_sock = accept(sock, (struct sockaddr *)&csin, &cslen);
				ret = read(sd, buf_client, 1000 - 1);
				{
					buf_client[ret] = '\0';
					printf("%s", buf_client);
					if (strcmp(buf_client, "quit\n") == 0)
					{
						Log.Closed();
						close(sock);
						EndOfDaemon();
					}
					Log.AddLog(buf_client);
				}
			}
		}
	}
	//closesocket(sock);
	perror("Exit");
	return (EXIT_SUCCESS);
}
