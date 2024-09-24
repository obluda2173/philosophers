/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:14:54 by erian             #+#    #+#             */
/*   Updated: 2024/09/16 17:49:18 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../Libft/libft.h"

int	to_c(char c);
int	to_s(char *str);
int	to_x(size_t n, char *hex);
int	to_p(void *ptr);
int	to_d(long long nbr);
int	ft_printf(const char *s, ...);

#endif