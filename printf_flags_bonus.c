/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flags_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:47:44 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/30 19:28:06 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"

static void num_reader(size_t *wid_prec, char *start, char *end, int i)
{
	while(start != end)
	{
		wid_prec[i] = wid_prec[i] * 10 + *start - 48;
		start++;
	}
	wid_prec[i] = wid_prec[i] * 10 + *start - 48;
}

static void	num_finder(size_t *wid_prec, char *start, char *end, int i)
{
	char	*num_end;
	char	*tmp_ptr;

	tmp_ptr = start;
	while(tmp_ptr != end)
	{
		if (ft_isdigit(*tmp_ptr))
			{
				while (tmp_ptr != end && ft_isdigit(*tmp_ptr))
				{
					num_end = tmp_ptr;
					tmp_ptr++;
				}
				num_reader(wid_prec, start, num_end, i);
				break ;
			}
		tmp_ptr++;
	}
}

static void	wid_spec_finder(char *start, char *end, char *f_flags, size_t *wid_prec)
{
	while (start != end && *start != '.')
	{
		if (*start == '0')
		{
			num_finder(wid_prec, start + 1, end, 0);
			f_flags[1] = '0';
			start++;
			break ;
		}
		else if (ft_isdigit(*start))
		{
			num_finder(wid_prec, start, end, 0);
			start++;
			break ;
		}
		start++;
	}
	while (start != end)
	{
		if (*start == '.')
		{
			num_finder(wid_prec, start + 1, end, 1);
			f_flags[2] = '.';
			return ;
		}
		start++;
	}
}

void	flag_finder(char *start, char *end, char *f_flags, size_t *wid_prec)
{
	char	*flags;
	char	*tmp_start;
	int		i;

	flags = "-# +";
	tmp_start = start;
	wid_spec_finder(start, end, f_flags, wid_prec);
	i = 0;
	while (i < 4)
	{
		while (start != end)
		{
			if (*start == flags[i])
			{
				f_flags[i + 3] = *start;
				break ;
			}
			start++;
		}
		start = tmp_start;
		i++;
	}
}
