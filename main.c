/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:37 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/05 20:09:48 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int	main(void)
{
	printf("\nprintf:\n");
	printf("return val: %d\n", printf("%5.1i", 0));
	printf("\nft_printf:\n");
	printf("return val: %d\n", ft_printf("%5.1i", 0));
	printf("\n");
}
