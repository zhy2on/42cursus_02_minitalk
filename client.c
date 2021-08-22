/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:24:14 by jihoh             #+#    #+#             */
/*   Updated: 2021/08/18 19:24:15 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "utils.h"

void	sig_handler(int signo)
{
	(void)signo;
	usleep(1000);
	return ;
}

int	send_pid(pid_t server_pid, pid_t client_pid)
{
	int	bit;
	int	signo;

	bit = 22;
	while (bit-- > 0)
	{
		if ((client_pid >> bit) & 1)
			signo = SIGUSR1;
		else
			signo = SIGUSR2;
		if (kill(server_pid, signo) == -1)
			return (-1);
		usleep(1000);
	}
	return (0);
}

int	send_char(pid_t server_pid, char c)
{
	int	bit;
	int	signo;

	bit = 8;
	while (bit-- > 0)
	{
		if ((c >> bit) & 1)
			signo = SIGUSR1;
		else
			signo = SIGUSR2;
		if (kill(server_pid, signo) == -1)
			return (-1);
		signal(SIGUSR1, sig_handler);
		pause();
	}
	return (0);
}

int	send_message(pid_t server_pid, char *str)
{
	while (*str)
	{
		if (send_char(server_pid, *str++) == -1)
			return (-1);
	}
	if (send_char(server_pid, '\0') == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	pid_t	client_pid;

	if (argc != 3)
	{
		write(2, "Usage: ./clinet [PID] [message]\n", 32);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	client_pid = getpid();
	if (send_pid(server_pid, client_pid) == -1
		|| send_message(server_pid, argv[2]) == -1)
	{
		write(2, "ERROR: Invalid server PID.\n", 27);
		return (1);
	}
	write(1, "Message sent successfully :)\n", 29);
	return (0);
}
