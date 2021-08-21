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

#include <signal.h>
#include <unistd.h>

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

int	send_pid(pid_t server_pid, pid_t client_pid)
{
	int	bit;
	int	signal;

	bit = 22;
	while (bit-- > 0)
	{
		if ((server_pid >> bit) & 1)
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		if (kill(server_pid, signal) == -1)
			return (-1);
		usleep(1000);
	}
	return (0);
}

int	send_message(pid_t server_pid, char *str)
{
	int	bit;
	int	signal;

	while (*str)
	{
		bit = 8;
		while (bit-- > 0)
		{
			if ((*str >> bit) & 1)
				signal = SIGUSR1;
			else
				signal = SIGUSR2;
			if (kill(server_pid, signal) == -1)
				return (-1);
			usleep(1000);
		}
		str++;
	}
	while (bit++ < 7)
	{
		if (kill(server_pid, SIGUSR2) == -1)
			return (-1);
		usleep(1000);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(2, "Usage: ./clinet [PID] [message]\n", 32);
		return (1);
	}
	if (send_message(ft_atoi(argv[1]), argv[2]) == -1)
	{
		write(2, "ERROR: Invalid server PID.\n", 27);
		return (1);
	}
	write(1, "Message sent successfully :)\n", 29);
	return (0);
}
