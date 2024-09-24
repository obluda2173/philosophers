/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:29:58 by erian             #+#    #+#             */
/*   Updated: 2024/08/08 22:11:38 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	to_c(char chr)
{
	write(1, &chr, 1);
	return (1);
}

int	to_s(char *str)
{
	if (str == NULL)
		return (to_s("(null)"));
	ft_putstr_fd(str, 1);
	return ((int)ft_strlen(str));
}

int	to_x(size_t n, char *hex)
{
	int		i;

	i = 0;
	if (n / 16)
		i += to_x(n / 16, hex);
	i += to_c(hex[n % 16]);
	return (i);
}

int	to_p(void *ptr)
{
	int	i;

	i = 0;
	if (ptr == 0)
		return (to_s("(nil)"));
	i += to_s("0x");
	i += to_x((size_t)ptr, "0123456789abcdef");
	return (i);
}

int	to_d(long long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count += to_c('-');
		nbr = -nbr;
	}
	if (nbr / 10)
		count += to_d(nbr / 10);
	count += to_c(nbr % 10 + '0');
	return (count);
}
