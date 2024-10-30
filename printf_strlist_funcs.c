/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_strlist_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:56:29 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/30 17:34:16 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

// The following functions manage: 
//	- creation of new strings from format string;
//	- adding formatted (created) strings to the list of all strings;
//	- clearing the list in case of an allocation error.

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
