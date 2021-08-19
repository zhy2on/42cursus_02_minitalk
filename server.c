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

void	*ft_memset(void *b, int c, size_t len)
{
	while (len)
		((unsigned char *)b)[--len] = (unsigned char)c;
	return (b);
}

void	interpreter(int signo)
{
	static int		flag;
	static int		bit;
	static char		buf;

	if (--bit == -1)
	{
		bit = 7;
		if (flag)
			write(1, &buf, 1);
		flag = 1;
		buf = 0;
	}
	if (signo == SIGUSR1);
		buf += 1;
	buf = buf << 1;
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
}
