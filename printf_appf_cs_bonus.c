/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_appf_cs_bonus.c                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:54:01 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/04 20:57:10 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"
#include <stdlib.h>

// The following function manages the application of flags/width 
// to formatted %i and %d variables.
// flags map:		"f0.-# +"
// ind map:		"0123456"
// used:		"-+++-++"
// wid_prec[0] - width, wid_prec[1] - precision ('.')

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

void	pad_zeroes(char *pad_str, char *conv_str, size_t pad_count)
{
	ft_memset(pad_str, '0', pad_count);
	while(*conv_str)
	{
		*(pad_str + pad_count) = *conv_str;
		pad_str++;
		conv_str++;
	}
}

void	pad_spaces(char *pad_str, char *conv_str, char sign, size_t pad_count)
{
	size_t	i;

	i = 0;
	printf("pad_count: %zu\n", pad_count);
	printf("dhjadsaconvvcxp: %s\n", conv_str); 
	printf("sign: %c\n", sign);
	if (sign)
	{
		pad_str[pad_count] = sign;
		i++;
		conv_str++;
	}
	while (*conv_str)
	{
		pad_str[pad_count + i] = *conv_str;
		i++;
		conv_str++;
		printf("check conv_str: %s\n", conv_str);
	}
	while(pad_count--)
		pad_str[pad_count] = ' ';
}

char	pad_decider(char *flags)
{
	char	pad;

	pad = '0';
	if (flags[2] == '.' || flags[1] != '0' ||  flags[3] == '-')
		pad = ' ';
	return (pad);
}

char	*app_wid(char *conv_str, size_t *wid_prec, size_t *l, char *flags)
{
	char	pad;
	char	*pad_str;
	size_t	pad_c;
	char	sign;
	char	neg;

	pad = pad_decider(flags);
	sign = check_sign(conv_str, flags);
	neg = (sign == '-');
	pad_c = wid_prec[0] - (sign != 0) - *l;
	if (conv_str[0] == '-')
			conv_str++;
	pad_str = (char *) calloc(1, wid_prec[0] - (sign != 0) + 1);
	if (pad == '0')
		pad_zeroes(pad_str, conv_str, pad_c);
	else if (flags[3] == '-')
	{
		pad_str[0] = sign * (sign != 0);
		ft_memcpy(pad_str + (sign != 0), conv_str, *l);
		ft_memset(pad_str + *l + (sign != 0), ' ', pad_c);
	}
	else
		pad_spaces(pad_str, conv_str, sign, pad_c);
	(*l) = wid_prec[0];
	return (pad_str);
}

char	*app_prec(char *conv_str, size_t zeroes_to_add, size_t *l, char neg)
{
	char	*prec_str;
	size_t	i;

	i = 0;
	printf("zeroes to add: %zu\n", zeroes_to_add);
	prec_str = (char*) malloc((*l - neg) + zeroes_to_add + 1);
	printf("check alloc: %zu\n", (*l - neg) + zeroes_to_add + 1);
	while(zeroes_to_add)
	{
		prec_str[i] = '0';
		zeroes_to_add--;
		i++;
	}
	ft_memcpy(&prec_str[i], conv_str + neg, *l + 1 - neg);
	free(conv_str);
	*l = *l - neg + i;
	printf("check length after perc: %zu\n", *l);
	printf("check string after prec: %s\n", prec_str);
	return (prec_str);
}

// The following function manages the application of flags/width 
// to formatted %i and %d variables.
// flags map:		"f0.-# +"
// ind map:		"0123456"
// used:		"-+++-++"
// wid_prec[0] - width, wid_prec[1] - precision ('.')
char	*app_flags_di(char *str, char *flags, size_t *wid_prec, size_t *l)
{
	char	neg;
	char	sign;

	sign = check_sign(str, flags);
	neg = (str[0] == '-');
	if (wid_prec[1] > *l - neg)
		str = app_prec(str, wid_prec[1] - (*l - neg), l, neg);
	if (str[0] == '-')
		(*l)--;
	if (wid_prec[0] > *l + (sign != 0))
	{
		str = app_wid(str, wid_prec, l, flags);
	}
	return (str);
}

// The following function manage the application of flags/width 
// to formatted %s and %c variables.
// flags map:		"f0.-# +"
// ind map:		"0123456"
// used:		"--++---"
// wid_prec[0] - width, wid_prec[1] - precision ('.')
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

