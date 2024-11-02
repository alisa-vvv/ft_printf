/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:37 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/02 17:42:31 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int	main(void)
{
//	printf("\nft_printf:\n");
//	printf("return val: %d\n", ft_printf("(%010.6i)\n", -12345));
	printf("\nprintf:\n");
	printf("return val: %d\n", printf("(%0 10i)\n", -12345));
	// if pec <= wid 6 - (4 - 3) = wid_prec[0] - (wid_prec[1] - len(w/o sign)) = 1 (count of zeroes)
	printf("\n");
}
