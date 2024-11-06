/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_appf_cs_bonus.c                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:54:01 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/06 19:54:25 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

// The following function manages the application of flags/width 
// to formatted %i and %d variables.
// flags map:		"f0.-# +"
// ind map:		"0123456"
// used:		"-+++-++"
// wid_prec[0] - width, wid_prec[1] - precision ('.')

static char	*prec_zero(char *orig_str, ssize_t *l)
{
	char	*str;

	free(orig_str);
	str = ft_strdup("");
	*l = 0;
	if (!str)
		return (NULL);
	return (str);
}

char	*app_flags_di(char *str, char *flags, ssize_t *wid_prec, ssize_t *l)
{
	char	neg;
	char	sign;
	size_t	pad_c;

	sign = check_sign(str, flags);
	neg = (str[0] == '-');
	if (wid_prec[1] <= 0 && str[0] == '0' && flags[2] == '.')
		str = prec_zero(str, l);
	else if (!wid_prec[0] && !wid_prec[1] && (!sign || neg))
		return (str);
	if (str != NULL && wid_prec[1] && wid_prec[1] > *l - neg)
		str = app_prec(str, wid_prec[1] - (*l - neg), l, neg);
	if (str != NULL && wid_prec[0]
		&& wid_prec[0] > *l + (sign != 0) - (str[0] == '-'))
	{
		if (str[0] == '-')
			(*l)--;
		pad_c = wid_prec[0] - *l - (sign != 0);
		str = app_wid(str, pad_c, l, flags);
	}
	if (str != NULL && sign && *str != '-')
		str = app_sign(str, l, sign);
	return (str);
}

// The following function manage the application of flags/width 
// to formatted %s and %c variables.
// flags map:		"f0.-# +"
// ind map:		"0123456"
// used:		"--++---"
// wid_prec[0] - width, wid_prec[1] - precision ('.')
char	*app_flags_cs(char *conv_str, char *flags, ssize_t *wid_prec, ssize_t *l)
{
	char	*modified_str;
	ssize_t	new_len;

	if (wid_prec[0] > *l)
	{
		new_len = wid_prec[0];
		modified_str = (char *) malloc ((new_len + 1) * sizeof(char));
		if (!modified_str)
			return (NULL);
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
