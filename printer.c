/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 14:50:19 by nkamolba          #+#    #+#             */
/*   Updated: 2017/11/22 17:01:40 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_getsigned(va_list ap, char length)
{
	if (length == 'H')
		return ((unsigned char)va_arg(ap, int));
	else if (length == 'h')
		return ((short int)va_arg(ap, int));
	else if (length == 'l')
		return (va_arg(ap, long int));
	else if (length == 'L')
		return (va_arg(ap, long long int));
	else if (length == 'j')
		return (va_arg(ap, intmax_t));
	else if (length == 'z')
		return (va_arg(ap, size_t));
	return (va_arg(ap, int));
}

size_t	ft_getunsigned(va_list ap, char length)
{
	if (length == 'H')
		return ((unsigned char)va_arg(ap, unsigned int));
	else if (length == 'h')
		return ((unsigned short)va_arg(ap, unsigned int));
	else if (length == 'l')
		return (va_arg(ap, unsigned long int));
	else if (length == 'L')
		return (va_arg(ap, unsigned long long int));
	else if (length == 'j')
		return (va_arg(ap, uintmax_t));
	else if (length == 'z')
		return (va_arg(ap, size_t));
	return (va_arg(ap, int));
}

size_t	ft_getnumbytype(va_list ap, t_printf *conv)
{
	size_t	n;

	n = 0;
	if (ft_strchr("di", conv->spec))
		n = ft_getsigned(ap, conv->length);
	else if (ft_strchr("ouxX", conv->spec))
		n = ft_getunsigned(ap, conv->length);
	return (n);
}

char	*ft_itoa_base(size_t n, char *base)
{
	int		base_len;
	int		num_len;
	size_t	tmp;
	char	*str;

	base_len = ft_strlen(base);
	num_len = 1;
	tmp = n;
	while (tmp /= base_len)
		num_len++;
	if (!(str = ft_strnew(num_len)))
		return (NULL);
	while (num_len)
	{
		str[--num_len] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}

char	*ft_numtostr(size_t n, char spec)
{
	char	*str;

	str = NULL;
	if (ft_strchr("diu", spec))
		str = ft_itoa(n);
	else if (spec == 'o')
		str = ft_itoa_base(n, "01234567");
	else if (spec == 'x')
		str = ft_itoa_base(n, "0123456789abcdef");
	else if (spec == 'X')
		str = ft_itoa_base(n, "0123456789ABCDEF");
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strfrontcat_free(char **str1, char *str2)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(str2, *str1)))
		return (NULL);
	free(*str1);
	*str1 = tmp;
	return (*str1);
}

char	*ft_strbackcat_free(char **str1, char *str2)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(*str1, str2)))
		return (NULL);
	free(*str1);
	*str1 = tmp;
	return (*str1);
}

char	*ft_handle_sharp(char spec, char **str)
{
	if (spec == 'o' && !(*str = ft_strfrontcat_free(str, "0")))
		return (NULL);
	else if (spec == 'x' && !(*str = ft_strfrontcat_free(str, "0x")))
		return (NULL);
	else if (spec == 'X' && !(*str = ft_strfrontcat_free(str, "0X")))
		return (NULL);
	return (*str);
}

char	*ft_handle_plus(char **str)
{
	if (ft_atoi(*str) >= 0)
	{
		if (!(*str = ft_strfrontcat_free(str, "+")))
			return (NULL);
	}
	return (*str);
}

char	*ft_handle_space(char **str)
{
	if (!(*str = ft_strfrontcat_free(str, " ")))
		return (NULL);
	return (*str);
}

char	*ft_handle_zero(char **str, int len, int width)
{
	char	*tmp;
	int		zero_len;
	int		i;
	int		j;

	if (!(tmp = ft_strnew(width)))
		return (NULL);
	zero_len = width - len;
	i = 0;
	j = 0;
	if (**str == '-' || **str == '+' || **str == ' ')
		tmp[i++] = str[0][j++];
	while (zero_len--)
		tmp[i++] = '0';
	while (j < len)
		tmp[i++] = str[0][j++];
	free(*str);
	*str = tmp;
	return (*str);
}

char	*ft_handle_precision_num(char **str, int len, int precision)
{
	int		sign;
	char	*tmp;
	int		zero_len;
	int		i;
	int		j;

	sign = 0;
	if (**str == '-' || **str == '+' || **str == ' ')
		sign = 1;
	if (!(tmp = ft_strnew(precision + sign)))
		return (NULL);
	zero_len = precision - len + sign;
	i = 0;
	j = 0;
	if (sign)
		tmp[i++] = str[0][j++];
	while (zero_len--)
		tmp[i++] = '0';
	while (j < len)
		tmp[i++] = str[0][j++];
	free(*str);
	*str = tmp;
	return (*str);
}

char	*ft_handle_minus(char **str, int len, int width)
{
	char	*tmp;
	char	*str2;

	if (!(tmp = ft_strnew(width)))
		return (NULL);
	if (!(str2 = ft_strnew(width - len)))
		return (NULL);
	str2 = ft_memset(str2, ' ', width - len);
	if (!(*str = ft_strbackcat_free(str, str2)))
		return (NULL);
	free(str2);
	return (*str);
}

char	*ft_handle_width(char **str, int len, int width)
{
	char	*tmp;
	char	*str2;

	if (!(tmp = ft_strnew(width)))
		return (NULL);
	if (!(str2 = ft_strnew(width - len)))
		return (NULL);
	str2 = ft_memset(str2, ' ', width - len);
	if (!(*str = ft_strfrontcat_free(str, str2)))
		return (NULL);
	free(str2);
	return (*str);
}

char	*ft_getnum(va_list ap, t_printf *conv)
{
	size_t	n;
	char	*str;

	n = ft_getnumbytype(ap, conv);
	if (!(str = ft_numtostr(n, conv->spec)))
		return (NULL);
	if (ft_strchr("oxX", conv->spec) && conv->flag_sharp)
		ft_handle_sharp(conv->spec, &str);
	if (ft_strchr("di", conv->spec) && conv->flag_plus && *str != '-')
		ft_handle_plus(&str);
	else if (ft_strchr("di", conv->spec) && conv->flag_space && *str != '-')
		ft_handle_space(&str);
	if (conv->has_precision && (size_t)conv->precision > ft_strlen(str))
		ft_handle_precision_num(&str, ft_strlen(str), conv->precision);
	else if (ft_strchr("dioux", conv->spec) && conv->flag_zero
			&& (size_t)conv->width > ft_strlen(str))
		ft_handle_zero(&str, ft_strlen(str), conv->width);
	if (conv->flag_minus && (size_t)conv->width > ft_strlen(str))
		ft_handle_minus(&str, ft_strlen(str), conv->width);
	else if ((size_t)conv->width > ft_strlen(str))
		ft_handle_width(&str, ft_strlen(str), conv->width);
	return (str);
}

char	*ft_handle_precision_string(char **str, int precision)
{
	char	*tmp;

	if (!(tmp = ft_strnew(precision)))
		return (NULL);
	while (precision-- >= 0)
		tmp[precision] = str[0][precision];
	free(*str);
	*str = tmp;
	return (*str);
}

char	*ft_getstr(va_list ap, t_printf *conv)
{
	char	*str;

	str = ft_strdup(va_arg(ap, char*));
	if (conv->has_precision)
		ft_handle_precision_string(&str, conv->precision);
	if (conv->flag_minus && (size_t)conv->width > ft_strlen(str))
		ft_handle_minus(&str, ft_strlen(str), conv->width);
	else if ((size_t)conv->width > ft_strlen(str))
		ft_handle_width(&str, ft_strlen(str), conv->width);
	return (str);
}

/*
char	*ft_getwchar(va_list ap, t_printf *conv)
{
	wchar	c;

	wchar = va_arg(ap, wchar);
	return (NULL);
}
*/

char	*ft_getdata(va_list ap, t_printf *conv)
{
	char	*str;

	str = NULL;
	if (ft_strchr("diouxX", conv->spec))
		str = ft_getnum(ap, conv);
	if (conv->spec == 's')
		str = ft_getstr(ap, conv);
	//printstr
	//printp
	return (str);
}
