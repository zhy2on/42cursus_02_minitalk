/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:46:35 by jihoh             #+#    #+#             */
/*   Updated: 2021/08/18 18:46:37 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "utils.h"
#include <stdio.h>
#define	BUFF_SIZE 4095

void	get_client_pid(pid_t *client_pid, int signo, int *flag)
{
	static int i;

	if (i++ < 22)
	{
		*client_pid <<= 1;
		if (signo == SIGUSR1)
			*client_pid += 1;
	}
	if (i == 22)
	{
		*flag = 1;
		i = 0;
	}
}

int	receive_message_sub(int *i, int *j, char **buf)
{
	if ((*buf)[*j] == '\0')
	{
		write(1, *buf, *j);
		free(*buf);
		*buf = NULL;
		*j = -1;
		return (1);
	}
	*i = 0;
	*j += 1;
	return (0);
}

void	receive_message(int signo, int *flag, pid_t *client_pid)
{
	static int	i;
	static int	j;
	static char	*buf;

	if (i++ < 8)
	{
		if (!buf)
			buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
		if (!buf)
			return ;
		buf[j] <<= 1;
		if (signo == SIGUSR1)
			buf[j] += 1;
	}
	if (i == 8)
	{
		if (receive_message_sub(&i, &j, &buf))
		{
			*flag = 0;
			*client_pid = 0;
		}
	}
}

void	sig_handler(int signo)
{
	static int			flag;
	static pid_t		client_pid;

	if (!flag)
	{
		get_client_pid(&client_pid, signo, &flag);
		return ;
	}
	kill(client_pid, SIGUSR1);
	receive_message(signo, &flag, &client_pid);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	(void)argv;
	if (argc != 1)
	{
		write(2, "Usage: ./server\n", 16);
		return (1);
	}
	else
	{
		server_pid = getpid();
		write(1, "Server is launched! PID: ", 25);
		ft_putnbr_fd(server_pid, 1);
		ft_putchar_fd('\n', 1);
		signal(SIGUSR1, sig_handler);
		signal(SIGUSR2, sig_handler);
		while (1)
			pause();
	}
	return (0);
}
