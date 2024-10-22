/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:53:21 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/22 17:45:17 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // testing only
#include <unistd.h>
#include <stdarg.h>

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

// KEEP IN MID: have to recognise backslash stufF



//int	type_va_decider(void const	*content, int const	type)
//{
//
//	if (type == 0) // to type a string
//	{
//		char const	*string_out;
//		string_out = (char *) content;
//		ft_strlen(string_out);
//		ft_lstnew()
//	}
//	return (1);
//}

//int	ft_printf(const char *format, ...)
//{
//	va_list		ptr_to_va_list;
//	int			argumentnum;
//
//	argumentnum = 0;
//	va_start(ptr_to_va_list, format);
//	printf("should be the first thing: %s\n", va_arg(ptr_to_va_list, char*));
//	type_va_decider(va_arg(ptr_to_va_list, char*), 0);
//	printf("should be int: %d\n", va_arg(ptr_to_va_list, int));
//	printf("should be char: %c\n", va_arg(ptr_to_va_list, char));
//	va_end(ptr_to_va_list);
//}

int	main(void)
{	
	char	*weee = "weeeeeee";

	printf("we go like this: %+20s - and then a newline\n", weee);
	printf("show me the adress: %zu\n", weee);
	printf("show me the adress in hex: %X\n", weee);
	printf("test a decimal: %+010i\n", 15);
//	ft_printf("im a format", "lmao", 1, 'c');
}