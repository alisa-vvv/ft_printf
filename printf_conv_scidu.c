/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_scidu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:03:35 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/29 16:47:05 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"
#include <stdlib.h>

char	*convert_str(char *next_var, t_strlst **out_lst) // VAR for 0/- (just), VAR FOR . (max), VAR for (width)
{
	char	*conv_str;
	size_t	str_len;

	if (!next_var)
	{
		conv_str = ft_strdup("(null)");
		if (!conv_str)
			return (NULL);
		str_len = ft_strlen(conv_str);
	}
	else
	{
		str_len = ft_strlen(next_var);
		conv_str = (char *) malloc(sizeof(char) * (str_len + 1));
		if (!conv_str)
			return (NULL);
		ft_memcpy(conv_str, next_var, str_len);
		conv_str[str_len] = '\0';
	}
	add_str_to_list(conv_str, out_lst, str_len);
	return (conv_str);
}

char	*convert_percent(t_strlst **out_lst)
{
	char	*conv_str;

	conv_str = (char *) malloc (sizeof(char) * 2);
	if (!conv_str)
		return (NULL);
	conv_str[0] = '%';
	conv_str[1] = '\0';
	add_str_to_list(conv_str, out_lst, 1);
	return (conv_str);
}

char	*convert_char(int next_var, t_strlst **out_lst) 
{
	char			*conv_str;

	conv_str = (char *)malloc (sizeof(char) * 2);
	if (!conv_str)
		return (NULL);
	conv_str[0] = (char)next_var;
	conv_str[1] = '\0';
	add_str_to_list(conv_str, out_lst, 1);
	return (conv_str);
}

char	*convert_int(int next_var, t_strlst **out_lst) // VAR for +/' ' (sign), VAR for 0/- (just), VAR for width
{
	char	*conv_str;
	int		str_len;

	conv_str = ft_itoa(next_var);
	if (!conv_str)
		return (NULL);
	str_len = ft_strlen(conv_str);
	add_str_to_list(conv_str, out_lst, str_len);
	return (conv_str);
}

char	*convert_uint(unsigned long long int next_var, t_strlst **out_lst) // VAR for +/' ' (sign), VAR for 0/- (just), VAR for width
{
	char	*conv_str;
	int		str_len;

	conv_str = ft_utoa(next_var);
	if (!conv_str)
		return (NULL);
	str_len = ft_strlen(conv_str);
	add_str_to_list(conv_str, out_lst, str_len);
	return (conv_str);
}
