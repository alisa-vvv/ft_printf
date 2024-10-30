/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:37 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/30 19:35:52 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int	main(void)
{
//	printf("chars printed: %d", printf(" %x ", 0));
//	printf("\n");
//	printf("chars printed: %d", ft_printf(" %x ", 0));
//	printf("return val: %d\n", ft_printf("check:(%0123.33s)\n", "12345"));
	printf("\nreturn val: %d\n", printf("%-55%"));
	printf("\n");
	printf("\nreturn val: %d\n", ft_printf("%-55%"));
}