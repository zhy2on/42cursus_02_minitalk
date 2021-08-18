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
	static size_t	i;
	static int		bit;
	static char		buf[100];

	if (--bit == -1)
	{
		bit = 6;
		++i;
	}
	buf[i] &= ~(1 << 7);
	if (signo == SIGUSR1)
		buf[i] |= (1 << bit);
	else if (signo == SIGUSR2)
		buf[i] &= ~(1 << bit);
	if (i == 99 || buf[i] == 127)
	{
		buf[i] = '\0';
		write(1, buf, i + 1);
		ft_memset(buf, '\0', 99);
		i = 0;
		bit = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	(void)argv;
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
		while (42)
		{
			signal(SIGUSR1, interpreter);
			signal(SIGUSR2, interpreter);
		}
	}
}
