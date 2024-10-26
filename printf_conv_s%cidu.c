/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conversions_01.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:03:35 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/26 15:51:14 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"
#include <stdlib.h>
#include <stdint.h>

char	*convert_str(void *next_var, t_strlst **out_lst)
{
	char	*conv_str;
	size_t	str_len;

	str_len = ft_strlen(next_var);
	conv_str = (char *) malloc(sizeof(char) * (str_len + 1));
	if (!conv_str)
		return (NULL);
	ft_memcpy(conv_str, next_var, str_len);
	conv_str[str_len] = '\0';
	add_str_to_list(conv_str, out_lst, str_len);
	return (conv_str);
}

char	*convert_percent(t_strlst **out_lst)
{
	char	*conv_str;

	conv_str = (char *) malloc (sizeof(char) * 2);
	if (!conv_str)
		return (NULL);
	conv_str[0] = 37;
	conv_str[1] = '\0';
	add_str_to_list(conv_str, out_lst, 1);
	return (conv_str);
}

char	*convert_char(void *next_var, t_strlst **out_lst)
{
	char	*conv_str;

	conv_str = (char *) malloc (sizeof(char) * 2);
	if (!conv_str)
		return (NULL);
	conv_str[0] = (int)(intptr_t)next_var;
	conv_str[1] = '\0';
	add_str_to_list(conv_str, out_lst, 1);
	return (conv_str);
}

char	*convert_int(void *next_var, t_strlst **out_lst)
{
	char	*conv_str;
	int		str_len;

	conv_str = ft_itoa((int)(intptr_t)next_var);
	if (!conv_str)
		return (NULL);
	str_len = ft_strlen(conv_str);
	add_str_to_list(conv_str, out_lst, str_len);
	return (conv_str);
}

char	*convert_uint(void *next_var, t_strlst **out_lst)
{
	char	*conv_str;
	int		str_len;

	conv_str = ft_utoa((unsigned int)(uintptr_t)next_var);
	if (!conv_str)
		return (NULL);
	str_len = ft_strlen(conv_str);
	add_str_to_list(conv_str, out_lst, str_len);
	return (conv_str);
}
