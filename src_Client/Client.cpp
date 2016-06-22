/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 15:36:24 by aleung-c          #+#    #+#             */
/*   Updated: 2016/06/22 15:36:26 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Matt_Daemon.hpp"

Client::Client( void )
{
	
}

Client::Client(Client const &src)
{
	*this = src;
}

Client::~Client( void )
{

}

Client		&Client::operator=(Client const & rhs)
{
	(void)rhs;
	return (*this);
}

// My methods

void			Client::usage()
{
	printf("Usage: [Address] [port]\n");
	exit(-1);
}

int				Client::check_arg1(char *arg)
{
	int port;

	port = atoi(arg);
	if (port > 49151 || port < 1024)
	{
		printf("Invalid port\n");
		return (-1);
	}
	return (0);
}

int		Client::check_args_client(int port)
{
	if (port > 49151 || port < 1024)
	{
		printf("Invalid port\n");
		return (-1);
	}
	return (0);
}


int		Client::create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (strcmp(addr, "localhost") == 0)
		sprintf(addr, "127.0.0.1");
	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("Connect error.\n");
		exit (-1);
	}
	printf("SUCCESS - Connected to server.\n");
	//printf("Port: %d\n", port);
	//printf("Client socket: %d\n", sock);
	return (sock);
}

void	Client::prompt(void)
{
	printf("~ Client $>");
}

void	Client::client_prompt(int sock)
{
	int		ret;
	char	buf[1000];

	while (1)
	{
		prompt();
		ret = read(0, buf, 999);
		buf[ret] = '\0';
		write(sock, buf, strlen(buf));
	}
}