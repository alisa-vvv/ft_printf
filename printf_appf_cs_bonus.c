/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_appf_cs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:54:01 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/30 19:33:53 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The following functions manage the application of flags/width 
// to formatted %s and %c variables.
// flags map:	"s0.-# +"
// ind map:		"0123456"
// used:		"---+---"
// wid_prec[0] - width, wid_prec[1] - precision ('.')

#include <stdio.h>

#include "ft_printf.h"
#include <stdlib.h>

char	*app_flags_cs(char *conv_str, char *flags, size_t *wid_prec, size_t *l)
{
	char	*modified_str;
	size_t	new_len;

	if (wid_prec[0] > *l)
	{
		new_len = wid_prec[0];
		modified_str = malloc ((new_len + 1) * sizeof(char));
		modified_str[new_len] = '\0';
		if (flags[3] == '-')
		{
			ft_memset(modified_str + *l, ' ', new_len - *l);
			ft_memcpy(modified_str, conv_str, *l);
		}
		else
		{
			ft_memset(modified_str, ' ', new_len - *l);
			ft_memcpy(modified_str + new_len - *l, conv_str, *l);
		}
		*l = new_len;
		free(conv_str);
		return (modified_str);
	}
	return (conv_str);
}
