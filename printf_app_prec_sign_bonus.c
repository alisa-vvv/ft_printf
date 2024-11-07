/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_app_prec_sign_bonus.c                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: avaliull <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/06 19:33:17 by avaliull       #+#    #+#                */
/*   Updated: 2024/11/07 17:46:17 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

char	check_sign(char *str, char *flags)
{
	if (*str == '-')
		return ('-');
	else if (flags[6] == '+')
		return ('+');
	else if (flags[5] == ' ')
		return (' ');
	return (0);
}

char	*app_prec(char *conv_str, size_t zeroes_to_add, ssize_t *l, char neg)
{
	char	*prec_str;
	size_t	i;

	if (!conv_str)
		return (NULL);
	i = 0;
	prec_str = (char *) malloc((*l - neg) + zeroes_to_add + 1);
	while (zeroes_to_add)
	{
		prec_str[i] = '0';
		zeroes_to_add--;
		i++;
	}
	ft_memcpy(&prec_str[i], conv_str + neg, *l + 1 - neg);
	free(conv_str);
	*l = *l - neg + i;
	return (prec_str);
}

char	*app_sign(char *conv_str, ssize_t *l, char sign)
{
	ssize_t	i;
	ssize_t	j;
	char	*signed_str;

	if (!conv_str)
		return (NULL);
	i = 0;
	j = 0;
	signed_str = (char *) malloc(*l + 2);
	if (*conv_str == ' ')
	{
		while (conv_str[i] == ' ')
		{
			signed_str[i] = conv_str[i];
			i++;
		}
	}
	signed_str[i] = sign;
	j = i + 1;
	while (i < *l)
		signed_str[j++] = conv_str[i++];
	signed_str[j] = '\0';
	(*l)++;
	free(conv_str);
	return (signed_str);
}
