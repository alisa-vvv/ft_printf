/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:33:13 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/26 15:33:33 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include "libft/libft.h"

typedef struct printf_lst
{
	char				*string;
	int					size;
	struct printf_lst	*next;
}						t_strlst;

typedef char *(func_ptr(void *, t_strlst **));

/*	PRIMARY FUNCTIONS	(these might become static later)*/
int	format_parser(char *format, ...);
char	*new_str(char *format, char *start, t_strlst **out_lst);
/*char	*format_reader(char *format, void* next_var, t_strlst **out_lst);*/
int	final_gigastring_out(t_strlst **out_lst);

/*	LIST MANIPULATION FUNCTIONS	(might also become static in sep. file)*/
t_strlst	*create_out_node(char *str_start, int len);
t_strlst	*add_str_to_list(char *str_start, t_strlst **out_lst, int len);
void	clr_lst(t_strlst **out_lst);

/*	CONVERSION FUNCTIONS	*/
char	*ft_utoa(unsigned int n);
char	*convert_str(void *next_var, t_strlst **out_lst);
char	*convert_char(void *next_var, t_strlst **out_lst);
char	*convert_percent(t_strlst **out_lst);
char	*convert_int(void *next_var, t_strlst **out_lst);
char	*convert_uint(void *next_var, t_strlst **out_lst);

#endif // FT_PRINTF_H