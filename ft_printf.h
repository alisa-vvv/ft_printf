/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:33:13 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/07 18:11:19 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdio.h>
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
int			final_gigastring_out(t_strlst **out_lst, int err_ovrr);

/*	LIST MANIPULATION FUNCTIONS	(might also become static in sep. file)*/
t_strlst	*create_out_node(char *str_start, int len);
t_strlst	*add_str_to_list(char *str_start, t_strlst **out_lst, int len);

/*	CONVERSION FUNCTIONS	*/
char		*ft_utoa(unsigned long long n);
char		*c_perc(t_strlst **out_lst);
char		*c_str(char *var, t_strlst **out_lst, char *flags, ssize_t *wid_prec);
char		*c_char(int var, t_strlst **out_lst, char *flags, ssize_t *wid_prec);
char		*c_int(int var, t_strlst **out_lst, char *flags, ssize_t *wid_prec);
char		*c_uint(unsigned long long var, t_strlst **out_lst);
char		*c_hexup(unsigned long long var, t_strlst **out_lst);
char		*c_hexlo(unsigned long long var, t_strlst **out_lst);
char		*c_ptr(void *var, t_strlst **out_lst);

/*	BONUS FUNCTIONS	*/
void	flag_finder(char *start, char *end, char *f_flags, ssize_t *wid_prec);
void	wid_spec_finder(char *start, char *end, char *f_flags, ssize_t *wid_prec);
char	*app_flags_cs(char *conv_str, char *flags, ssize_t *wid_prec, ssize_t *l);
char	*app_flags_di(char *conv_str, char *flags, ssize_t *wid_prec, ssize_t *l);
char	*app_wid(char *conv_str, size_t pad_c, ssize_t *l, char *flags);
char	check_sign(char *str, char *flags);
char	*app_prec(char *conv_str, size_t zeroes_to_add, ssize_t *l, char neg);
char	*app_sign(char *conv_str, ssize_t *l, char sign);

#endif // FT_PRINTF_H
