/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:53:21 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/29 18:53:24 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"

//FUNCTIONS FOR FORMATS:
// for each one - a function for: minimum width, right or left-justifying, zerofill for ints
// for %c, %s, %% - just make a string out of them, %% as exception, very easy;
// for %p - convert adress to hexidecimal string;
// for %d - just itoa;
// for %i - itoa and convert it to octal/hexa if necessary;
// for %u - itoa without negative case;
// for %x - convert to hex with lowwercase;
// for %X - convert to hex with uppercase;
// backslash test

//KEEP IN MIND: have to recognise backslash chars(doesnt seem to be necessay, i think it just works)

//%[flags][width][.precision][length]type
//%[-+ #0][(number)][.number][letters00]
// 0 - can be added after, or spaces instead if width is present
// if '-' - left-justfy (can add after conversion)
// if '+' - add + if needed and not just minus, do after conversion, before left-justification
// if ' ' - add ' ' if value is pos, negates plus, do after conversion, before justification
// if '#' - add prefix for x and X, convert pointer to hex
// if '.', use 
// width - use 
// Flags can be in any order, but redundancy is ignored.
// Field width and precision must follow flags and precede the type specifier.
// The type specifier is always last.


//TODO:
// Function to count the specifier lenth, calloc an arr for each specifier and width;
// pass width and specifier arr to conversion funcs (if needed);
// conversion funcs have additional conditions that call for flag-applier functions in _bonus files;
// profit


// CREATE A LIST OF FUNCITON POINTERS TO APPLY AFTER SCANNING 

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

void	wid_prec_finder(int *wid_prec, char *start, char *end, char *f_flags) // TO BONUS
{
	char	*num_end;
	char	*tmp_ptr;

	tmp_ptr = start;
	while(tmp_ptr != end)
	{
		if (ft_isdigit(*start))
			{
				while (tmp_ptr != end && ft_isdigit(*start))
				{
					num_end = tmp_ptr;
					tmp_ptr++;
				}
				break ;
			}
		start++;
	}
}

void	flag_finder(char *start, char *end, char *f_flags int *wid_prec) // TO BONUS
{
	char	*flags;
	char	*tmp_start;
	char	*occ_0;
	char	*occ_dot;

	flags = "-# +";
	i = 0;
	tmp_start = start;
	wid_prec_finder(wid_prec);
	while (i < 5)
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
		f_flags[i + 1] = '=';
		start = tmp_start;
		i++;
	}
	// FIRST WE FIND THE FIRST OCCURANCE OF A TYPE SPEC, THIS WILL BE THE END OF SPEC (POTENTIALY ANY ALPHA?)
	// THEN WE FIND ALL THE FLAGS  ('.' NOT A FLAG)
	// AFTER FLAGS CAN ONLY BE NUMBERS/DOT/TYPE, ATOI NUMBERS TO GET WIDTH (MIN LEN), JUST 0 OR - WIDTH = 0
	// AFTER NUMBERS CAN ONLY BE DOT/TYPE
	// AFTER DOT CAN ONLY BE NUMBERS/TYPE, NUMBERS AFTER DOT = MAXSTRLEN
	// AFTER NUMBERS CAN ONLY BE TYPE
}

char	*conv_chooser(char *format, int *spec_len)
{
	char	*found_specs;
	char	*spec_start;
	int		wid_prec[3];

	spec_start = format;
	found_specs = (char *) ft_calloc(sizeof(char), 8);
	if (!found_specs)
		return (NULL);
	*spec_len = 1;
	while (*format && *format != '%' && *format != 'c' && *format != 's'
	&& *format != 'd' && *format != 'i' && *format != 'p'
	&& *format != 'u' && *format != 'x' && *format != 'X')
	{
		format++;
		*spec_len++;
	}
	wid_prec[2] = 0;
	flag_finder(spec_start, spec_end, found_flags, wid_prec);
	found_specs[0] = *format;
	return (found_specs);
}

char	*format_parser(char *f_ptr, va_list f_va, t_strlst **out_lst, char *str_start)
{
	int				spec_len;
	char			*conv_arr;
	char			*checker;
	
	spec_len = 0;
	conv_arr = conv_chooser(f_ptr + 1, &spec_len);
	if (*str_start != '%' && *str_start != '\0')
	{
		if (!new_str(f_ptr, spec_len, str_start, out_lst))
		{
			free(conv_arr); // THIS IS TEMP, REPLACE FOR LIST CLEARING LATER
			clr_lst(out_lst);
			return (NULL);
		}
	}
	if (*conv_arr == '%')
		checker = convert_percent(out_lst);
	if (*conv_arr == 'c')
		checker = convert_char((int)va_arg(f_va, int), out_lst);
	else if (*conv_arr == 's')
		checker = convert_str(va_arg(f_va, char *), out_lst);
	else if (*conv_arr == 'd' || *conv_arr == 'i')
		checker = convert_int(va_arg(f_va, int), out_lst);
	else if (*conv_arr == 'u')
		checker = convert_uint(va_arg(f_va, unsigned int), out_lst);
	else if (*conv_arr == 'p')
		checker = convert_ptr(va_arg(f_va, void *), out_lst);
	else if (*conv_arr == 'x')
		checker = convert_hex_low(va_arg(f_va, unsigned int), out_lst);
	else if (*conv_arr == 'X')
		checker = convert_hex_cap(va_arg(f_va, unsigned int), out_lst);
	free(conv_arr); // THIS IS TEMP, REPLACE FOR LIST CLEARING LATER
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
