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

void	interpreter(int signo)
{
	static int		i;
	static int		j;
	static char		*buf = NULL;

	if (i++ < 8)
	{
		if (!buf)
			buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
		if (!buf)
			return ;
		buf[j] <<= 1;
		if (signo == SIGUSR1)
			buf[j] += 1;
	}
	if (i == 8)
	{
		if (buf[j] == '\0')
		{
			write(1, buf, j);
			free(buf);
			buf = NULL;
		}
		i = 0;
		j++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 1)
	{
		write(2, "Usage: ./server\n", 16);
		return (1);
	}
	else
	{
		pid = getpid();
		write(1, "Server is launched! PID: ", 25);
		ft_putnbr_fd(pid, 1);
		ft_putchar_fd('\n', 1);
		while (1)
		{
			signal(SIGUSR1, interpreter);
			signal(SIGUSR2, interpreter);
		}
	}
	return (0);
}
