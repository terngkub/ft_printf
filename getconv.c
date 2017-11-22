/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getconv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 14:04:07 by nkamolba          #+#    #+#             */
/*   Updated: 2017/11/22 16:18:37 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_getflag(const char **format, t_printf *conv)
{
	while (ft_strchr("#0-+ ", **format))
	{
		if (**format == '#')
			conv->flag_sharp += 1;
		else if (**format == '0')
			conv->flag_zero += 1;
		else if (**format == '-')
			conv->flag_minus += 1;
		else if (**format == '+')
			conv->flag_plus += 1;
		else if (**format == ' ')
			conv->flag_space += 1;
		if (conv->flag_sharp > 1 || conv->flag_zero > 1 || conv->flag_minus > 1
				|| conv->flag_plus > 1 || conv->flag_space > 1)
			return (0);
		*format += 1;
	}
	if ((conv->flag_zero && conv->flag_minus)
			|| (conv->flag_plus && conv->flag_space))
		return (0);
	return (1);
}

static int	ft_getwp(const char **format, t_printf *conv)
{
	if (ft_isdigit(**format))
	{
		conv->width = ft_atoi(*format);
		*format += ft_numlen(conv->width);
	}
	if (**format == '.')
	{
		*format += 1;
		if (!ft_isdigit(**format))
			return (0);
		conv->has_precision = 1;
		conv->precision = ft_atoi(*format);
		*format += ft_numlen(conv->precision);
	}
	return (1);
}

static void	ft_getlength(const char **format, t_printf *conv)
{
	if (ft_strchr("hljz", **format))
	{
		conv->length = **format;
		*format += 1;
		if (ft_strchr("hl", conv->length) && ft_strchr("hl", **format))
		{
			if (**format == 'h')
				conv->length = 'H';
			else if (**format == 'l')
				conv->length = 'L';
			*format += 1;
		}
	}
}

static int	ft_checkspec(t_printf *conv)
{
	if (conv->flag_sharp && !ft_strchr("oOuUxX", conv->spec))
		return (0);
	if (conv->flag_zero && !ft_strchr("dDioOuUxX", conv->spec))
		return (0);
	if ((conv->flag_plus || conv->flag_space) && !ft_strchr("dDi", conv->spec))
		return (0);
	if (conv->length != 0 && conv->length != 'l'
			&& ft_strchr("cs", conv->spec))
		return (0);
	if (conv->length && ft_strchr("CSp", conv->spec))
		return (0);
	if (conv->length && ft_strchr("DOU", conv->spec))
		conv->spec = ft_tolower(conv->spec);
	if (!conv->length && ft_strchr("DOUCS", conv->spec))
	{
		conv->spec = ft_tolower(conv->spec);
		conv->length = 'l';
	}
	return (1);
}

int		ft_getconv(const char **format, t_printf *conv)
{
	if (!ft_getflag(format, conv))
		return (0);
	if (!ft_getwp(format, conv))
		return (0);
	ft_getlength(format, conv);
	if (ft_strchr("sSpdDioOuxXcC", **format))
	{
		conv->spec = **format;
		if (!ft_checkspec(conv))
		{
			printf("error");
			return (0);
		}
		return (1);
	}
	return (0);
}
