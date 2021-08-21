/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 21:43:02 by jihoh             #+#    #+#             */
/*   Updated: 2021/08/21 21:43:15 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <unistd.h>

int		ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif