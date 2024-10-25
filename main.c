/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:37 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/25 19:01:04 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{	
	printf("\nTOTAL LEN: %d\n", format_parser("12%s56%s90\n", "34", "78"));
	//printf("test correction: %c\n", 'a');
	//int	i = 'a';
	//printf("test: %i\n", i);
	//printf("return value: %d\n", printf("12345"));
}