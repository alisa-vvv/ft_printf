/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:33:13 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/02 17:09:14 by avaliull       ########   odam.nl        */
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
int			ft_printf(const char *format, ...);
char		*new_str(char *format, int spec_len, char *start, t_strlst **out_lst);
int			final_gigastring_out(t_strlst **out_lst);

/*	LIST MANIPULATION FUNCTIONS	(might also become static in sep. file)*/
t_strlst	*create_out_node(char *str_start, int len);
t_strlst	*add_str_to_list(char *str_start, t_strlst **out_lst, int len);
void		clr_lst(t_strlst **out_lst);

/*	CONVERSION FUNCTIONS	*/
char		*ft_utoa(unsigned long long n);
char		*c_perc(t_strlst **out_lst);
char		*c_str(char *next_var, t_strlst **out_lst, char *flags, size_t *wid_prec);
char		*c_char(int next_var, t_strlst **out_lst, char *flags, size_t *wid_prec);
char		*c_int(int next_var, t_strlst **out_lst, char *flags, size_t *wid_prec);
char		*c_uint(unsigned long long next_var, t_strlst **out_lst);
char		*c_hexup(unsigned long long next_var, t_strlst **out_lst);
char		*c_hexlo(unsigned long long next_var, t_strlst **out_lst);
char		*c_ptr(void *next_var, t_strlst **out_lst);

/*	BONUS FUNCTIONS	*/
void	flag_finder(char *start, char *end, char *f_flags, size_t *wid_prec);
void	wid_spec_finder(char *start, char *end, char *f_flags, size_t *wid_prec);
char	*app_flags_cs(char *conv_str, char *flags, size_t *wid_prec, size_t *l);
char	*app_flags_di(char *conv_str, char *flags, size_t *wid_prec, size_t *l);

#endif // FT_PRINTF_H
