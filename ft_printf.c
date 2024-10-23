/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:53:21 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/23 19:47:04 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // testing only
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"

typedef struct pf_list
{
	char 	*string;
	int				size;
	struct pf_list	*next;
}					str_list;

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


static void	clr_lst(str_list **out_lst)
{
	str_list	*next_node;

	while (*out_lst != NULL)
	{
		next_node = (*out_lst)->next;
		free((*out_lst)->string);
		free(*out_lst);
		*out_lst = next_node;
	}
}

static int	final_gigastring_out(str_list **out_lst)
{
	str_list	*current_node;
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

static str_list	*create_out_node(char *str_start, int len)
{
	str_list	*new_node;

	new_node = (str_list *) malloc(sizeof(str_list));
	if (!new_node)
		return (NULL);
	new_node->string = str_start;
	new_node->size = len;
	new_node->next = NULL;
	return (new_node);
}

static str_list	*add_str_to_list(char *str_start, str_list **out_lst, int len)
{
	str_list	*next_node;
	str_list	*last_node;
	
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

static char	*format_reader(char *format, void* next_var, str_list **out_lst)
{
	char			*conv_str;
	char			*found_spec;
	char			*specs;
//	char			*flags;
	int				spec_len;
	int				str_len;

//	flags = "-0.# +";
	specs = "cspdiuxX";
	found_spec = ft_strchr(specs, *format);
	if (!found_spec)
		return (NULL);
	if (*found_spec == 's')
	{
		str_len = ft_strlen(next_var);
		conv_str = malloc(sizeof(char) * (str_len + 1));
		if (!conv_str)
			return (NULL);
		ft_memcpy(conv_str, next_var, str_len);
		conv_str[str_len] = '\0';
		add_str_to_list(conv_str, out_lst, str_len);
	}
	/*here would be the while loop to check for flags and gets the pointer to next char after*/
	spec_len = 1;
	return (format); // THIS SHOULD RETURN THE POINT TO LAST CHAR OF FORMAT, EDIT FOR BONUS
}

char	*str_creator(char *format, char *str_start, str_list **out_lst, char *next_var)
{
	char	*new_str;

	new_str = malloc((format - str_start) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str_start, format - str_start);
	int	test = format - str_start;
	if (!add_str_to_list(new_str, out_lst, format - str_start))
		return (NULL);
	format = format_reader((format + 1), next_var, out_lst);
	return (format + 1);
}

int	format_parser(char *format, ...)
{
	char		*str_start;
	void		*next_var;
	va_list		f_va;
	str_list	*out_lst;


	out_lst = NULL;
	str_start = format;
	va_start(f_va, format);
	while (*format)
	{
		if (*format == '%')
		{
			next_var = va_arg(f_va, void*);
			str_start = str_creator(format, str_start, &out_lst, next_var);
		}
		format++;
	}	
	if (!add_str_to_list(ft_strdup(str_start), &out_lst, format - str_start - 1))
		return (0);
	va_end(f_va);
	return (final_gigastring_out(&out_lst));
}

int	main(void)
{	
printf("\nTOTAL LEN: %d\n", format_parser("123%s56%s89\n", "4", "7"));
}