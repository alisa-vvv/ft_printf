/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_pxx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:43:45 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/28 15:20:03 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <stdint.h>

#include <stdio.h>

static int	calc_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

static char	*to_hex(unsigned int n, char *symbols, int *len)
{
	char	*conv_str;
	int		i;

	*len += calc_len(n);
	i = *len;
	conv_str = (char *) malloc(sizeof(char) * (*len + 1));
	if (!conv_str)
		return (NULL);
	conv_str[i] = '\0';
	while (n)
	{
		i--;
		conv_str[i] = symbols[n % 16];
		n /= 16;
	}
	return (conv_str);
}

char	*convert_hex_cap(unsigned int next_var, t_strlst **out_lst)
{
	char			*conv_str;
	int				len;

	len = 0;
	conv_str = to_hex(next_var, "0123456789ABCDEF", &len);
	if (!conv_str)
		return (NULL);
	add_str_to_list(conv_str, out_lst, len);
	return (conv_str);
}

char	*convert_hex_low(unsigned int next_var, t_strlst **out_lst)
{
	char			*conv_str;
	int				len;

	len = 0;
	conv_str = to_hex(next_var, "0123456789abcdef", &len);
	if (!conv_str)
		return (NULL);
	add_str_to_list(conv_str, out_lst, len);
	return (conv_str);
}

char	*convert_ptr(void *next_var, t_strlst **out_lst)
{
	char			*conv_str;
	int				len;
	unsigned int	ptr_val;

	len = 2;
	ptr_val = (unsigned int)(uintptr_t)next_var;
	if (!ptr_val)
	{
		conv_str = ft_strdup("(nil)");
		if (!conv_str)
			return (NULL);
		len = 5;
	}
	else
	{
		conv_str = to_hex(ptr_val, "0123456789abcdef", &len);
		conv_str[0] = '0';
		conv_str[1] = 'x';
	}
	add_str_to_list(conv_str, out_lst, len);
	return (conv_str);
}
