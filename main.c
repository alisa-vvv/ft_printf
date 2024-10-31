/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:37 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/31 19:57:44 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int	main(void)
{
	printf("\nft_printf:\n");
	printf("return val: %d\n", ft_printf("(%05.4i)\n", -123));
	printf("\nprintf:\n");
	printf("return val: %d\n", printf("(%05.4i)\n", -123));
	// if pec <= wid 6 - (4 - 3) = wid_prec[0] - (wid_prec[1] - len(w/o sign)) = 1 (count of zeroes)
	printf("\n");
}