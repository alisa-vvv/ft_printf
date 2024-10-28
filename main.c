/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:37 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/28 17:38:10 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdint.h>

int	main(void)
{
	printf("chars printed: %d", printf("%c ", '0' + 256));
	printf("\n");
	printf("chars printed: %d", ft_printf("%c ", '0' + 256));
	printf("\n");
	printf("chars printed: %d", printf("12%s56%d90\n", "34", 78));
	printf("\n");
	printf("chars printed: %d", ft_printf("12%s56%d90\n", "34", 78));
	printf("\n");
}