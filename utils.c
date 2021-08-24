/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:24:14 by jihoh             #+#    #+#             */
/*   Updated: 2021/08/24 15:00:56 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

char	*ft_buf_alloc(char *buf, int idx, int size)
{
	char	*new_buf;

	new_buf = (char *)malloc(sizeof(char) * ((idx / size + 1) * size));
	if (!new_buf)
	{
		write(1, "Error: Fail to buffer allocation\n", 33);
		free(buf);
		exit(1);
	}
	while (--idx >= 0)
		new_buf[idx] = buf[idx];
	free(buf);
	return (new_buf);
}

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
