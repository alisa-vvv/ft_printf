/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:53:21 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/29 14:11:09 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"

/*Here are the requirements:
• Don’t implement the buffer management of the original printf().
• Your function has to handle the following conversions: cspdiuxX%
• Your function will be compared against the original printf().
• You must use the command ar to create your library.
Using the libtool command is forbidden.
• Your libftprintf.a has to be created at the root of your repository.
5
ft_printf Because ft_putnbr() and ft_putstr() aren’t enough
You have to implement the following conversions:
• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign. */

//PROTOTYPE1: 	1) find format;
//				2) store in a list node along with the content of the var;
//					2.5) add a check so that we have the same amount of formats and vars and they're correct;
//				3) list will contain a format specifier + contnt;
//				4) return a string to write for each thing;
//				5) make a big string with all the strings;
//				6) write that!

//PROTOTYPE2(CURRENT):
//				1) parse the format string;
//				2) once a % is encountered, pass the void ptr to next arg to subfuncs:
//					2.1) add the string from beginning of format str until % to the linked list;
//						!!!!! NEED TO ADD CHECK FOR IF STRING EMPTY !!!!!
//					2.2) check which format specifier is used + check for additional specs;
//					2.3) convert arg to str (if needed), apply additional specs, add str to the list;
//					2.4) return the pointer to the next char after specifier ends;
//				3) continue parsing until end of format string;
//				4) add the string from last format spec to end of format string to the list;
//				5) write the megalist to fd=1
//				6) win

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


// CREATE A LIST OF FUNCITON POINTERS TO APPLY AFTER SCANNING 

void	clr_lst(t_strlst **out_lst)
{
	t_strlst	*next_node;

	while (*out_lst != NULL)
	{
		next_node = (*out_lst)->next;
		free((*out_lst)->string);
		free(*out_lst);
		*out_lst = next_node;
	}
}

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

t_strlst	*create_out_node(char *str_start, int len)
{
	t_strlst	*new_node;

	new_node = (t_strlst *) malloc(sizeof(t_strlst));
	if (!new_node)
		return (NULL);
	new_node->string = str_start;
	new_node->size = len;
	new_node->next = NULL;
	return (new_node);
}

t_strlst	*add_str_to_list(char *str_start, t_strlst **out_lst, int len)
{
	t_strlst	*next_node;
	t_strlst	*last_node;

	next_node = create_out_node(str_start, len);
	if (!next_node)
		return (NULL);
	if (!*out_lst)
	{
		*out_lst = next_node;
		return (*out_lst);
	}
	last_node = *out_lst;
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = next_node;
	return (*out_lst);
}

char	*new_str(char *format, int spec_len, char *start, t_strlst **out_lst)
{
	char	*new_str;

	new_str = malloc((format - start + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	new_str [format - start] = '\0';
	ft_memcpy(new_str, start, format - start);
	if (!add_str_to_list(new_str, out_lst, format - start))
		return (NULL);
	return (format + spec_len);
}

char	*conv_chooser(char *format, int *spec_len)
{
	char	*found_specs;
//	char	*specs;

//	specs = "-0.# +";
	found_specs = (char *) malloc(sizeof(char) * 8);
	if (!found_specs)
		return (NULL);
	*spec_len = 1;
	while (*format && *format != '%' && *format != 'c' && *format != 's'
		&& *format != 'd' && *format != 'i' && *format != 'p'
		&& *format != 'u' && *format != 'x' && *format != 'X')
	{
		format++;
		//this will be expanded for bonus
	}
	found_specs[0] = *format;
	found_specs[1] = '\0';
	return (found_specs);
	// THIS SHOOULD CALCULATE LENTTH
	// ALL RETURNS SHOULD BE REPLACED WITH ADDING FUNC TO A LIST
}

int	ft_printf(const char *format, ...)
{
	char			*str_start;
	va_list			f_va;
	t_strlst		*out_lst;
	char			*conv_arr;
	int				spec_len;
	char			*checker;

	out_lst = NULL;
	spec_len = 0;
	str_start = (char *) format;
	va_start(f_va, format);
	while (*format) // this while loop and last string print should probably be it's own function
	{
		if (*format == '%')
		{
			conv_arr = conv_chooser((char *)format + 1, &spec_len);
			if (*str_start != '%' && *str_start != '\0')
			{
				if (!new_str((char *)format, spec_len, str_start, &out_lst))
				{
					clr_lst(&out_lst);
					return (0);
				}
			}
			if (*conv_arr == '%')
				checker = convert_percent(&out_lst);
			if (*conv_arr == 'c')
				checker = convert_char((int)va_arg(f_va, int), &out_lst);
			else if (*conv_arr == 's')
				checker = convert_str(va_arg(f_va, char *), &out_lst);
			else if (*conv_arr == 'd' || *conv_arr == 'i')
				checker = convert_int(va_arg(f_va, int), &out_lst);
			else if (*conv_arr == 'u')
				checker = convert_uint(va_arg(f_va, unsigned int), &out_lst);
			else if (*conv_arr == 'p')
				checker = convert_ptr(va_arg(f_va, void *), &out_lst);
			else if (*conv_arr == 'x')
				checker = convert_hex_low(va_arg(f_va, unsigned int), &out_lst);
			else if (*conv_arr == 'X')
				checker = convert_hex_cap(va_arg(f_va, unsigned int), &out_lst);
			free(conv_arr); // THIS IS TEMP, REPLACE FOR LIST CLEARING LATER
			if (!checker)
			{
				clr_lst(&out_lst);
				return (0);
			}
			format += spec_len;
			str_start = (char *)format + 1;
		}
		if (*format)
			format++;
	}
	va_end(f_va);
	/*	this is to print the remainder of format str after end is reached	*/
	if (*str_start != '%' && *str_start != '\0')
	{
		if (!add_str_to_list(ft_strdup(str_start), &out_lst, format - str_start))
			return (0);
	}
	/*	end																	*/
	return (final_gigastring_out(&out_lst));
}
