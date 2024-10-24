/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:35:56 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/10 15:36:11 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	signed char	sign;
	int			newint;

	sign = 1;
	newint = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (sign * newint);
		newint = newint * 10 + *str - 48;
		str++;
	}
	return (sign * newint);
}
