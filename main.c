/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:37 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/06 18:59:17 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int	main(void)
{
	printf("\nprintf:\n");
	printf("return val: %d\n", printf("%.0s", NULL));
	printf("\nft_printf:\n");
	printf("return val: %d\n", ft_printf("%.0s", NULL));
	printf("\n");
}
