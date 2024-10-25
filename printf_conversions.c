/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:03:35 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/25 19:06:33 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"
#include <stdlib.h>

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

//char	*convert_char(void *next_var, t_strlst **out_lst)
//{
//	char	*conv_str;
//
//	conv_str = (char *) malloc (sizeof(char) * 2);
//	if (!conv_str)
//		return (NULL);
//	conv_str[0] = next_var;
//	conv_str[1] = '\0';
//	add_str_to_list(conv_str, out_lst, 1);
//	printf("conv_str: %s\n", conv_str);
//	return (conv_str);
//}

//int	main(void)
//{
//	prin
//}