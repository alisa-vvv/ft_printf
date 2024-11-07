/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_appf_cs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:49:47 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/07 19:52:05 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

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

// The following function manages the application of flags/width 
// to formatted %i and %d variables.
// flags map:		"f0.-# +"
// ind map:			"0123456"
// used:			"-+++-++"
// w_p[0] - width, w_p[1] - precision ('.')
char	*appf_di(char *str, char *flags, ssize_t *w_p, ssize_t *l)
{
	char	neg;
	char	sign;
	size_t	pad_c;

	sign = check_sign(str, flags);
	neg = (str[0] == '-');
	if (w_p[1] <= 0 && str[0] == '0' && flags[2] == '.')
		str = prec_zero(str, l);
	else if (!w_p[0] && !w_p[1] && (!sign || neg))
		return (str);
	if (str != NULL && w_p[1] && w_p[1] > *l - neg)
		str = app_prec(str, w_p[1] - (*l - neg), l, neg);
	if (str != NULL && w_p[0]
		&& w_p[0] > *l + (sign != 0) - (str[0] == '-'))
	{
		if (str[0] == '-')
			(*l)--;
		pad_c = w_p[0] - *l - (sign != 0);
		str = app_wid(str, pad_c, l, flags);
	}
	if (str != NULL && sign && *str != '-')
		str = app_sign(str, l, sign);
	return (str);
}

// The following function manage the application of flags/width 
// to formatted %s and %c variables.
// flags map:		"f0.-# +"
// ind map:			"0123456"
// used:			"--++---"
// w_p[0] - width, w_p[1] - precision ('.')
char	*appf_cs(char *conv_str, char *flags, ssize_t *w_p, ssize_t *l)
{
	char	*modified_str;
	ssize_t	new_len;

	if (w_p[0] > *l)
	{
		new_len = w_p[0];
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
