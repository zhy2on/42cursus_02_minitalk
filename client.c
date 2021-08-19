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

int	check_return(int sign)
{
	if (sign < 0)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	num;
	int				cnt;

	sign = 1;
	num = 0;
	cnt = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str++ - '0');
		cnt++;
	}
	if (cnt > 20)
		return (check_return(sign));
	return (sign * num);
}

static int	send_ascii(pid_t pid, char c)
{
	int	bit;
	int	ret;

	bit = 7;
	while (bit-- > 0)
	{
		if (c & (1 << bit))
			ret = kill(pid, SIGUSR1);
		else
			ret = kill(pid, SIGUSR2);
		if (ret == -1)
			return (-1);
		usleep(1000);
	}
	return (0);
}

static int	send_message(pid_t pid_server, char *str)
{
	int	i;

	i = 0;
	while (str[i] >= 32 && str[i] <= 126)
	{
		if (send_ascii(pid_server, str[i]) == -1)
			return (-1);
		i++;
	}
	i = 0;
	while (i < 7)
	{
		if (kill(pid_server, SIGUSR1) == -1)
			return (-1);
		usleep(1000);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	pid_server;

	if (argc != 3)
	{
		write(2, "Usage: ./clinet [PID] [message]\n", 32);
		return (1);
	}
	pid_server = ft_atoi(argv[1]);
	if (send_message(pid_server, argv[2]) == -1)
	{
		write(2, "ERROR: Invalid server PID.\n", 27);
		return (1);
	}
	write(1, "Message sent successfully :)\n", 29);
	return (0);
}
