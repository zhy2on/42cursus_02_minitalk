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
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	unsigned int	num;
	int				cnt;

	num = 0;
	cnt = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str++ - '0');
		cnt++;
	}
	if (cnt > 20)
		return (-1);
	return (num);
}

void	sig_handler(int signo)
{
	(void)signo;
}

void	send_pid(pid_t server_pid, pid_t client_pid)
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
		{
			write(2, "Error: Invalid server PID\n", 26);
			exit(1);
		}
		usleep(10000);
	}
}

void	send_message(pid_t server_pid, char c)
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
		{
			write(2, "Error: Invalid server PID\n", 26);
			exit(1);
		}
		if (c || bit)
		{
			if (!usleep(100000))
			{
				write(2, "Error: Time out\n", 16);
				exit(1);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	signal(SIGUSR1, sig_handler);
	if (argc != 3)
	{
		write(2, "Usage: ./clinet [PID] [message]\n", 32);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	send_pid(server_pid, getpid());
	while (*argv[2])
		send_message(server_pid, *argv[2]++);
	send_message(server_pid, '\0');
	usleep(100);
	write(1, "Message sent successfully\n", 26);
	return (0);
}
