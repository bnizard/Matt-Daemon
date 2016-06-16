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

}

Daemon::~Daemon( void )
{

}

int		Daemon::create_server(int port)
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
		printf("error bind");
		exit (-1);
	}

	printf("Port: %d\n", port);
	printf("Server socket: %d\n", sock);
	listen(sock, 42);
	printf("- Awaiting connections... -\n");
	return (sock);
}

int Daemon::main_test ()
{

 	pid_t				pid;
 	std::ofstream		outputFile;
// 	int 				i = 0;
 	int					sock;
 	int					client_sock;
 	char				buf_client[1000];
	
	unsigned int		cslen;
	struct sockaddr_in	*csin;
	int ret;

	ret = 0;

  	//Fork the Parent Process
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

    outputFile.open("test2.txt");
	sock = create_server(4242);
	client_sock = accept(sock, (struct sockaddr *)&csin, &cslen);
	while ((ret = read(client_sock, buf_client, 1000 - 1)))
	{
		buf_client[ret] = '\0';
		outputFile << buf_client;
	}
	std::cout << "exit after read\n";
	return (EXIT_SUCCESS);
}