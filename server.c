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
#define	BUFF_SIZE 320

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	nb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}

int	send_ack(int client_pid, int signo)
{
	if (signo == SIGUSR1)
		kill(client_pid, SIGUSR1);
	else if (signo == SIGUSR2)
		kill(client_pid, SIGUSR2);
	else
	{
		write(2, "Invalid signal\n", 15);
		return (-1);
	}
	return (0);
}

void	sig_handler(int signo)
{
	static int		flag;
	static int		client_pid;
	static int		i;
	static int		j;
	static char		*buf = NULL;

/*
	if (!flag)
	{
		if (i++ < 22)
		{
			client_pid <<= 1;
			if (signo == SIGUSR1)
				client_pid += 1;
		}
		if (i == 22)
		{
			flag = 1;
			i = 0;
		}
		return ;
	}
	if (send_ack(client_pid, signo) == -1)
		return ;
		*/
	if (i++ < 8)
	{
		if (!buf)
			buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
		if (!buf)
			return ;
		buf[j] <<= 1;
		if (signo == SIGUSR1)
			buf[j] += 1;
		if (i != 8)
			return ;
	}
	if (buf[j] == '\0')
	{
		write(1, buf, j);
		free(buf);
		buf = NULL;
		j = -1;
	}
	i = 0;
	j++;
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	pid_t	client_pid;

	if (argc != 1)
	{
		write(2, "Usage: ./server\n", 16);
		return (1);
	}
	else
	{
		client_pid = 0;
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
