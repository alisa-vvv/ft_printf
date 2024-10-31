/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:53:21 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/31 16:59:21 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"

//%[flags][width][.precision][length]type
//%[-+ #0][(number)][.number][letters00]

int	final_gigastring_out(t_strlst **out_lst)
{
	t_strlst	*current_node;
	int			total_len;

	total_len = 0;
	current_node = *out_lst;
	while (current_node != NULL)
	{
		write(1, current_node->string, current_node->size);
		total_len += current_node->size;
		current_node = current_node->next;
	}
	clr_lst(out_lst);
	return (total_len);
}

char	*conv_chooser(char *format, int *spec_len, size_t *wid_prec)
{
	char		*found_flags;
	char		*spec_start;

	spec_start = format;
	found_flags = (char *) ft_calloc(sizeof(char), 8);
	if (!found_flags)
		return (NULL);
	ft_memset(found_flags, '=', 7);
	*spec_len = 1;
	while (*format && *format != '%' && *format != 'c' && *format != 's'
	&& *format != 'd' && *format != 'i' && *format != 'p'
	&& *format != 'u' && *format != 'x' && *format != 'X')
	{
		format++;
		(*spec_len)++;
	}
	if (*format != '%')
		flag_finder(spec_start, format, found_flags, wid_prec);
	found_flags[0] = *format;
	return (found_flags);
}

char	*format_parser(char *f_ptr, va_list f_va, t_strlst **out_lst, char *str_start)
{
	int				spec_len;
	char			*flags;
	char			*checker;
	size_t			wid_prec[2];
	
	spec_len = 0;
	wid_prec[0] = 0;
	wid_prec[1] = 0;
	flags = conv_chooser(f_ptr + 1, &spec_len, wid_prec);
	if (*str_start != '%' && *str_start != '\0')
	{
		if (!new_str(f_ptr, spec_len, str_start, out_lst))
		{
			free(flags); // THIS IS TEMP, REPLACE FOR LIST CLEARING LATER
			clr_lst(out_lst);
			return (NULL);
		}
	}
	if (*flags == '%')
		checker = c_perc(out_lst);
	if (*flags == 'c')
		checker = c_char((int)va_arg(f_va, int), out_lst, flags, wid_prec);
	else if (*flags == 's')
		checker = c_str(va_arg(f_va, char *), out_lst, flags, wid_prec);
	else if (*flags == 'd' || *flags == 'i')
		checker = c_int(va_arg(f_va, int), out_lst, flags, wid_prec);
	else if (*flags == 'u')
		checker = c_uint(va_arg(f_va, unsigned int), out_lst);
	else if (*flags == 'p')
		checker = c_ptr(va_arg(f_va, void *), out_lst);
	else if (*flags == 'x')
		checker = c_hexlo(va_arg(f_va, unsigned int), out_lst);
	else if (*flags == 'X')
		checker = c_hexup(va_arg(f_va, unsigned int), out_lst);
	// Maybe add another else check for when specifier is incorrect? to print the string anyway
	free(flags); // THIS IS TEMP, REPLACE FOR LIST CLEARING LATER
	if (!checker)
	{
		clr_lst(out_lst);
		return (NULL);
	}
	return (f_ptr + spec_len);
}

int	ft_printf(const char *format, ...)
{
	char			*str_start;
	va_list			f_va;
	t_strlst		*out_lst;
	char			*f_ptr;

	out_lst = NULL;
	f_ptr = (char *) format;
	str_start = f_ptr;
	va_start(f_va, format);
	while (*f_ptr) // this while loop and last string print should probably be it's own function
	{
		if (*f_ptr == '%')
		{
			f_ptr = format_parser(f_ptr, f_va, &out_lst, str_start);
			if (!f_ptr)
				return (0);
			str_start = f_ptr + 1;
		}
		if (*f_ptr)
			f_ptr++;
	}
	va_end(f_va);
	/*	this is to print the remainder of format str after end is reached	*/
	if (*str_start != '%' && *str_start != '\0')
	{
		if (!add_str_to_list(ft_strdup(str_start), &out_lst, f_ptr - str_start))
			return (0);
	}
	/*	end																	*/
	return (final_gigastring_out(&out_lst));
}
