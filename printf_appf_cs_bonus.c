/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_appf_cs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:54:01 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/31 19:58:48 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>

#include "ft_printf.h"
#include <stdlib.h>

char	*sign_applier(char *conv_str, size_t *l, char *flags)
{
	char	*mod_str;
	char	sign;
	
	sign = 0;
	if (flags[5] == ' ' && conv_str[0] != '-' && flags[6] != '+')
		sign = ' ';
	if (flags[6] == '+' && conv_str[0] != '-')
		sign = '+';
	if (sign)
	{
		mod_str = (char *) malloc((*l + 2) * sizeof(char));
		if (!mod_str)
			return (NULL);
		mod_str[0] = sign;
		ft_memcpy(mod_str + 1, conv_str, *l);
		free(conv_str);
		(*l)++;
	}
	else
		return (conv_str);
	return(mod_str);
}

char	*width_padder(size_t new_len, size_t *l, char *mod_str, char *flags)
{
	char	pad;
	char	*padded_str;

	pad = ' ';
	if (flags[1] == '0' && flags[2] != '.')
		pad = '0';
	padded_str = malloc ((new_len + 1) * sizeof(char));
	if (!padded_str)
		return (NULL);
	padded_str[new_len] = '\0';
	if (flags[3] == '-')
	{
		ft_memset(padded_str + *l, ' ', new_len - *l);
		ft_memcpy(padded_str, mod_str, *l);
	}
	else
	{
		if (pad  == '0')
		{
			*padded_str = *mod_str;
			ft_memset(padded_str + 1, pad, new_len - *l);
			ft_memcpy(padded_str + 1 + new_len - *l, mod_str + 1, *l);
		}
		else
		{
			*(padded_str + new_len - *l) = *mod_str;
			ft_memset(padded_str, pad, new_len - *l);
			ft_memcpy(padded_str + new_len - *l, mod_str, *l);
		}
	}
	*l = new_len;
	free(mod_str);
	return (padded_str);
}

// The following function manage the application of flags/width 
// to formatted %s and %c variables.
// flags map:	"f0.-# +"
// ind map:		"0123456"
// used:		"---+---"
// wid_prec[0] - width, wid_prec[1] - precision ('.')


// The following function manage the application of flags/width 
// to formatted %i and %d variables.
// flags map:	"f0.-# +"
// ind map:		"0123456"
// used:		"-+++-++"
// wid_prec[0] - width, wid_prec[1] - precision ('.')

char	*app_flags_di(char *conv_str, char *flags, size_t *wid_prec, size_t *l)
{
	char	*mod_str;
	char	*padded_str;
	size_t	len_tstr;
	char	sign_box;

	len_tstr = *l - (*conv_str == '-');
	mod_str = sign_applier(conv_str, l, flags);
	if (!mod_str)
		return (NULL);
	if (wid_prec[0] > *l)
		padded_str = width_padder(wid_prec[0], l, mod_str, flags);
	else
		padded_str = width_padder(*l, l, mod_str, flags);
	if (flags[2] == '.')
	{
		printf("len_tstr: %zu\n", len_tstr);
		if (wid_prec[1] > len_tstr)
			if (wid_prec[1] < wid_prec[0])
				sig
				printf("cinfusion\n");
	}
	if (!padded_str)
		return (NULL);
	return (padded_str);
}

char	*app_flags_cs(char *conv_str, char *flags, size_t *wid_prec, size_t *l)
{
	char	*modified_str;
	size_t	new_len;

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