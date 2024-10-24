/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:50:23 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/14 14:08:43 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*uc_dest;
	unsigned char	*uc_src;

	uc_dest = (unsigned char *) dest;
	uc_src = (unsigned char *) src;
	if (!dest && !src)
		return (0);
	if (dest <= src)
	{
		while (n--)
			*uc_dest++ = *uc_src++;
	}
	else if (dest > src)
	{
		uc_src += n - 1;
		uc_dest += n - 1;
		while (n--)
			*uc_dest-- = *uc_src--;
	}
	return (dest);
}
