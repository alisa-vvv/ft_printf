/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:30:09 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/16 13:04:29 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	recwrite(long tmpn, int fd)
{
	char	c;

	if (tmpn < 10)
	{
		c = tmpn + 48;
		write(fd, &c, 1);
		return ;
	}
	c = tmpn % 10 + 48;
	recwrite(tmpn / 10, fd);
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	tmpn;

	tmpn = n;
	if (n < 0)
	{
		tmpn = -tmpn;
		write(fd, "-", 1);
	}
	recwrite(tmpn, fd);
}
