/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:37 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/26 14:53:50 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdint.h>

int	main(void)
{	
	int	value = 012;
	unsigned int	ptr_value;
	void	*ptr = 0;
	ptr_value = (unsigned int)(uintptr_t) ptr;

	printf("\nTOTAL LEN: %d\n", format_parser("123%s678%s%c%%%d\n", "45", "9", '0', 0X100));
	printf("testing with scanf %i", value);
	printf("okay test then: %s\n", ft_itoa(value));
	printf("extracting number: %u\n", ptr_value);
	printf("printing with %%p: %p\n", ptr);
}