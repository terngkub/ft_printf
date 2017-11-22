/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:38:51 by nkamolba          #+#    #+#             */
/*   Updated: 2017/11/22 16:28:10 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

char	*ft_readword(const char **format, char *str)
{
	char	*str2;
	char	*tmp;

	if (!(str2 = ft_getword(*format, '%')))
		return (NULL);
	*format += ft_strlen(str2) - 1;
	if (!(tmp = ft_strjoin(str, str2)))
		return (NULL);
	free(str);
	str = tmp;
	return (str);
}

char	*ft_readpercent(const char **format, char *str)
{
	char	*str2;
	char	*tmp;

	if (!(str2 = ft_strnew(ft_strlen(str) + 1)))
		return (NULL);
	*str2 = '%';
	*format += 1;
	if (!(tmp = ft_strjoin(str, str2)))
		return (NULL);
	free(str);
	str = tmp;
	return (str);
}

void	ft_initconv(t_printf *conv)
{
	conv->flag_sharp = 0;
	conv->flag_zero = 0;
	conv->flag_minus = 0;
	conv->flag_plus = 0;
	conv->flag_space = 0;
	conv->width = 0;
	conv->has_precision = 0;
	conv->precision = 0;
	conv->length = 0;
	conv->spec = 0;
}

char	*ft_readconv(const char **format, va_list ap, char *str)
{
	t_printf	conv;
	char		*str2;

	ft_initconv(&conv);
	if (!(ft_getconv(format, &conv)))
		return (NULL);
	if (!(str2 = ft_getdata(ap, &conv)))
		return (NULL);
	ft_strbackcat_free(&str, str2);
	return (str);
}

void	ft_test(const char *format)
{
	t_printf	conv;

	ft_initconv(&conv);
	if (!ft_getconv(&format, &conv))
		printf("error\n");
	printf("%d\n", (int)conv.flag_sharp);
	printf("%d\n", (int)conv.flag_zero);
	printf("%d\n", (int)conv.flag_minus);
	printf("%d\n", (int)conv.flag_plus);
	printf("%d\n", (int)conv.flag_space);
	printf("%d\n", conv.width);
	printf("%d\n", (int)conv.has_precision);
	printf("%d\n", conv.precision);
	printf("%c\n", conv.length);
	printf("%c\n", conv.spec);
}


char	*ft_readformat(const char *format, va_list ap)
{
	char	*str;

	if (!(str = ft_strnew(0)))
		return (NULL);
	while (*format)
	{
		if (*format == '%' && *(format + 1) == '%')
		{
			if (!(str = ft_readpercent(&format, str)))
				return (NULL);
		}
		else if (*format == '%')
		{
			format++;
			if (!(str = ft_readconv(&format, ap, str)))
				return (NULL);
		}
		else if (!(str = ft_readword(&format, str)))
			return (NULL);
		format++;
	}
	return (str);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	char		*str;
	int			len;

	va_start(ap, format);
	if (!(str = ft_readformat(format, ap)))
		return (-1);
	va_end(ap);
	ft_putstr(str);
	len = ft_strlen(str);
	free(str);
	return (len);
}
