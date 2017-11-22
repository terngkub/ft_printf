/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:41:29 by nkamolba          #+#    #+#             */
/*   Updated: 2017/11/22 15:37:40 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef struct	s_printf
{
	char		flag_sharp;
	char		flag_zero;
	char		flag_minus;
	char		flag_plus;
	char		flag_space;
	int			width;
	char		has_precision;
	int			precision;
	char		length;
	char		spec;
}				t_printf;

int				ft_printf(const char *format, ...);
int				ft_getconv(const char **format, t_printf *conv);
char			*ft_getdata(va_list ap, t_printf *conv);
char			*ft_strbackcat_free(char **str1, char *str2);

#endif
