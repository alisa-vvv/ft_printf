/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   count_wid_prec.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: avaliull <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/02 17:07:32 by avaliull       #+#    #+#                */
/*   Updated: 2024/11/02 17:08:01 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"

static char *num_read(size_t *wid_prec, char *start, char *end, int i)
{
	while(start != end)
	{
		wid_prec[i] = wid_prec[i] * 10 + *start - 48;
		start++;
	}
	wid_prec[i] = wid_prec[i] * 10 + *start - 48;
	return (start);
}

static char	*num_finder(size_t *wid_prec, char *start, char *end, int i)
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
				tmp_ptr = num_read(wid_prec, start, num_end, i);
				break ;
			}
		tmp_ptr++;
	}
	return (tmp_ptr);
}

static char	*wid_counter(size_t *wid_prec, char *start, char *end, int i)
{
	char	*num_end;
	char	*tmp_ptr;

	while ((*start == '+' || *start == '-' || *start == '#' ||
	*start == ' ') && *start != '.')
			start++;
	tmp_ptr = start;
	while(tmp_ptr != end && *tmp_ptr != '.')
	{
		if (ft_isdigit(*tmp_ptr))
			{
				while (tmp_ptr != end && ft_isdigit(*tmp_ptr))
				{
					num_end = tmp_ptr;
					tmp_ptr++;
				}
				start = num_read(wid_prec, start, num_end, i);
				break ;
			}
		tmp_ptr++;
	}
	return (tmp_ptr);
}

static void	spec_finder(char *start, char *end, char *flags, size_t *wid_prec)
{
	while (start != end)
	{
		if (*start == '.')
		{
			num_finder(wid_prec, start + 1, end, 1);
			flags[2] = '.';
			return ;
		}
		start++;
	}
}

void	wid_spec_finder(char *start, char *end, char *f_flags, size_t *wid_prec)
{
	while (start != end && *start != '.')
	{
		if (*start == '0')
		{
			start = wid_counter(wid_prec, start + 1, end, 0);
			f_flags[1] = '0';
			break ;
		}
		else if (ft_isdigit(*start))
		{
			start = num_finder(wid_prec, start, end, 0);
			start++;
			break ;
		}
		start++;
	}
	spec_finder(start, end, f_flags, wid_prec);
}

