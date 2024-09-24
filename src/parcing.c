/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:55:58 by erian             #+#    #+#             */
/*   Updated: 2024/09/24 15:25:11 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-') 
		exit_error("Invalid number\n");
	if (!(*str >= '0' && *str <= '9'))
		exit_error("Invalid number\n");
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result > INT_MAX)
		exit_error("Too large number\n");
	return (result);
}

void	parse(char **av, t_table *table)
{
	table->ph_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		exit_error("Invalid given time\n");
	if (av[5])
		table->max_meal = ft_atol(av[5]);
	else
		table->max_meal = -1;
		
}
