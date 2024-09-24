/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:13:02 by erian             #+#    #+#             */
/*   Updated: 2024/08/08 22:24:35 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_and_count(const char *format, va_list *args)
{
	if (*format == 'c')
		return (to_c(va_arg(*args, int)));
	else if (*format == 's')
		return (to_s(va_arg(*args, char *)));
	else if (*format == 'p')
		return (to_p(va_arg(*args, void *)));
	else if (*format == 'd' || *format == 'i')
		return (to_d(va_arg(*args, int)));
	else if (*format == 'u')
		return (to_d(va_arg(*args, unsigned int)));
	else if (*format == 'x')
		return (to_x(va_arg(*args, unsigned int), "0123456789abcdef"));
	else if (*format == 'X')
		return (to_x(va_arg(*args, unsigned int), "0123456789ABCDEF"));
	else if (*format == '%')
		return (to_c('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			count += print_and_count(++format, &args);
		else
			count += to_c(*format);
		format++;
	}
	va_end(args);
	return (count);
}
