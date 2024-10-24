/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:16:37 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/19 11:59:42 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	if (!dest && !src)
		return (0);
	ptr_dest = (unsigned char *) dest;
	ptr_src = (unsigned char *) src;
	while (n--)
		*ptr_dest++ = *ptr_src++;
	return (dest);
}
