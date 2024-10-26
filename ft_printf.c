/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:53:21 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/26 14:37:37 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // testing only
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
	printf("\t\t\tADDED STRING: %s\n", new_node->string);
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

char	*new_str(char *format, char *start, t_strlst **out_lst)
{
	char	*new_str;

	printf("tesitng start inside new_str: %s+\n", start);
	if (*start != '%')
	{
		new_str = malloc((format - start) * sizeof(char));
		if (!new_str)
			return (NULL);
		ft_memcpy(new_str, start, format - start);
		if (!add_str_to_list(new_str, out_lst, format - start))
			return (NULL);
	}
	printf("testing format inside new_str: %s\n", format);
	return (format + 2);
}

func_ptr	*conv_chooser(char *format, int *form_len)
{
	char			*found_type;
	char			*types;

	types = "%cspdiuxX";
	found_type = ft_strchr(types, *format);
	*form_len = 1; // THIS SHOOULD CALCULATE LENTTH
	if (!found_type || *found_type == '%')
		return (NULL);
	if (*found_type == 's')
		return (convert_str); // ALL RETURNS SHOULD BE REPLACED WITH ADDING FUNC TO A LIST
	if (*found_type == 'c')
		return (convert_char);
	if (*found_type == 'd' || *found_type == 'i')
		return (convert_int);
	return (NULL);
}

int	format_parser(char *format, ...)
{
	char			*str_start;
	void			*next_var;
	va_list			f_va;
	t_strlst		*out_lst;
	func_ptr		*conv_f;
	int				form_len;

	out_lst = NULL;
	form_len = 0;
	str_start = format;
	va_start(f_va, format);
	while (*format)
	{
		if (*format == '%')
		{	
			conv_f = conv_chooser(format + 1, &form_len);
			if (conv_f)
			{
				next_var = va_arg(f_va, void*);
				str_start = new_str(format, str_start, &out_lst);
				conv_f(next_var, &out_lst);
				format += form_len;
			}
			else
			{
				convert_percent(&out_lst);
				str_start = new_str(format, str_start, &out_lst);
				format++;
			}
		}
		format++;
		printf("testing format inside parser: %s\n", format);
	}
	va_end(f_va);
	printf("testing last start: %s\n", str_start);
	char	*teststr = ft_strdup(str_start);
	free(teststr);
	if (!add_str_to_list(ft_strdup(str_start), &out_lst, format - str_start))
		return (0);
	return (final_gigastring_out(&out_lst));
}
