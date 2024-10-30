/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_scidu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:03:35 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/30 19:27:47 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"
#include <stdlib.h>

// The following functions manage conversions for %c, %%, %s %i to string;
// After conversion, functions to apply bonus flags and manage width are called;
// The resulting strings are passed to add_str_to_list for writing later;
// Return is either NULL or the ptr to converted string for error-checking.

char	*c_str(char *next_var, t_strlst **out_lst, char *flags, size_t *wid_prec)
{
	char	*conv_str;
	size_t	str_len;

	if (!next_var)
	{
		conv_str = ft_strdup("(null)");
		if (!conv_str)
			return (NULL);
		str_len = ft_strlen(conv_str);
		if (flags[2] == '.' && wid_prec[1] < str_len)
			str_len = wid_prec[1];
	}
	else
	{
		str_len = ft_strlen(next_var);
		if (flags[2] == '.' && wid_prec[1] < str_len)
			str_len = wid_prec[1];
		conv_str = (char *) malloc(sizeof(char) * (str_len + 1));
		if (!conv_str)
			return (NULL);
		ft_memcpy(conv_str, next_var, str_len);
		conv_str[str_len] = '\0';
	}
	conv_str = app_flags_cs(conv_str, flags, wid_prec, &str_len);
	add_str_to_list(conv_str, out_lst, str_len);
	return (conv_str);
}

char	*c_perc(t_strlst **out_lst)
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

char	*c_char(int next_var, t_strlst **out_lst, char *flags, size_t *wid_prec) 
{
	char	*conv_str;
	size_t	str_len;

	conv_str = (char *)malloc (sizeof(char) * 2);
	if (!conv_str)
		return (NULL);
	conv_str[0] = (char)next_var;
	conv_str[1] = '\0';
	str_len = 1;
	conv_str = app_flags_cs(conv_str, flags, wid_prec, &str_len);
	add_str_to_list(conv_str, out_lst, str_len);
	return (conv_str);
}

char	*c_int(int next_var, t_strlst **out_lst) // VAR for +/' ' (sign), VAR for 0/- (just), VAR for width
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

char	*c_uint(unsigned long long next_var, t_strlst **out_lst) // VAR for +/' ' (sign), VAR for 0/- (just), VAR for width
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
