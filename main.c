/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:37 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/26 15:48:33 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdint.h>

int	main(void)
{	
	int	value = 012;
	unsigned int	ptr_value;
	char	*ptr = "123";
	ptr_value = (unsigned int)(uintptr_t) ptr;

	printf("\nTOTAL LEN: %d\n", format_parser("test u: %u\n.", -345));;
	printf("testing with scanf %i", value);
	printf("okay test then: %s\n", ft_itoa(value));
	printf("extracting number: %u\n", ptr_value);
	printf("printing with %%p: %p\n", ptr);
}