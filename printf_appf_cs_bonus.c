/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_appf_cs_bonus.c                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:54:01 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/02 19:02:48 by avaliull       ########   odam.nl        */
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

//char	*sign_applier(char *conv_str, size_t *l, char *flags)
//{
//	char	*mod_str;
//	size_t	i;
//	char	sign;
//	
//	sign = 0;
//	i = 0;
//	if (flags[5] == '+')
//		sign = '+';
//	else if (flags[5] == ' ')
//		sign = ' ';
//	if (flags[3] == '-')
//	{
//		if (conv_str[0] == '-')
//			return (conv_str);
//		mod_str = (char *)malloc(sizeof(char) * (*l + 1));
//		mod_str[0] == sign;
//		ft_memcpy((mod_str + 1), conv_str, *l + 1);
//		(*l)++;
//		return (mod_str);
//	}
//	while(conv_str[i] == ' ')
//		i++;
//	if (conv_str[i] == '-')
//		return (conv_str);
//	conv_str[i - 1] = sign;
//	mod_str = (char *)malloc(sizeof(char) * (*l + 1));
//	mod_str[0] =
//	return(mod_str);
//}

char	check_sign(char *conv_str, char *flags)
{
	if (*conv_str == '-')
		return ('-');
	else if (flags[6] == '+')
		return ('+');
	else if (flags[5] == ' ')
		return (' ');
	return (0);
}	

void	pad_zeroes(char *pad_str, char sign, size_t pad_count, char *conv_str)
{
	if (sign)
	{
		pad_str[0] = sign;
		pad_str++;
	}
	ft_memset(pad_str, '0', pad_count);
	ft_memcpy(pad_str, conv_str + (sign == '-'), *l - (sign == '-'));
}

void	pad_spaces(char *pad_str, char sign, size_t pad_count, char *conv_str)
{
	if (sign)
	{
		*pad_str == sign;
		pad_str++;
	}
	ft_memset(pad_str, ' ', pad_count);
}


//UGH change this shomehow this is dumb as fuck
char	*app_wid(char *conv_str, size_t *wid_prec, size_t *l, char *flags)
{
	char	pad;
	char	*pad_str;
	size_t	pad_count;
	char	sign;

	pad = '0';
	sign = check_sign(conv_str, flags);
	if (flags[2] == '.' || flags[1] != '0' ||  flags[3] == '-')
		pad = ' ';
	pad_count = wid_prec[0] - (*l - (sign == '-')) - (sign != 0);
	pad_str = (char *) malloc(wid_prec[0] + 2 - (sign == '-'));
	if (pad == '0')
		pad_zeroes(pad_str, sign, pad_count, conv_str);
	else if (flags[3] == '-')
	{
		pad_str[0] = sign;
		ft_strlcpy(pad_str + (sign == '-'), conv_str + (sign == '-'), *l);
		pad_spaces(pad_str, sign, pad_count, conv_str);
	}
	else
	{
		pad_spaces(pad_str + pad_count, sign, pad_count, conv_str);
		ft_memcpy(pad_str +
	}
}

char	*app_prec(char *conv_str, size_t zeroes_to_add, size_t *l, int neg)
{
	char	*prec_str;
	size_t	i;
	
	i = 0;
	prec_str = (char*) malloc(sizeof(char) * (*l + zeroes_to_add));
	if (neg)
	{
		prec_str[0] = '-';
		i++;
	}
	while(zeroes_to_add)
	{
		prec_str[i] = '0';
		zeroes_to_add--;
		i++;
	}
	ft_memcpy(&prec_str[i], conv_str + neg, *l + 1 - neg);
	free(conv_str);
	*l = *l + i - neg;
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
	printf("check wid_prec[1] == %zu\n", wid_prec[1]);
	int	neg;
	char	sign;

	sign = 0;
	neg = (str[0] == '-');
	if (wid_prec[1] > *l - neg)
	{
		printf("check\n");
		str = app_prec(str, wid_prec[1] - *l + neg, l, neg);
	}
	if (wid_prec[0] > *l)
		str = app_wid(str, wid_prec, l, neg);
	printf("testing prec application: (%s)\n", str);
	printf("checking new length after prec: %zu\n", *l);
	flags++;
       	flags--;	// REMOVE THIS
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

