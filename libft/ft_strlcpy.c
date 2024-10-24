/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:48:52 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/19 14:41:24 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen((char *) src);
	if (size == 0)
		return (src_len);
	if (src_len + 1 < size)
		size = src_len;
	else
		size -= 1;
	while (size--)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}
