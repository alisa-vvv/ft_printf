/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:58:33 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/21 16:49:57 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr_start;

	if (nmemb > (size_t) - 1 / size)
		return (NULL);
	ptr_start = malloc(nmemb * size);
	if (ptr_start == NULL)
		return (NULL);
	ft_bzero(ptr_start, nmemb * size);
	return (ptr_start);
}
