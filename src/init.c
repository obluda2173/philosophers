/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:02:25 by erian             #+#    #+#             */
/*   Updated: 2024/09/28 10:25:05 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	cstm_atoi(const char *str)
{
	long	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-') 
		print_exit(NULL, "Invalid number.\n");
	if (!(*str >= '0' && *str <= '9'))
		print_exit(NULL, "Invalid number.\n");
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result > INT_MAX)
		print_exit(NULL, "Too large number.\n");
	return (result);
}
long	get_current_time(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philosopher) * data->ph_nbr);
	if (!data->philosophers)
		return (1);
	i = -1;
	while (++i < data->ph_nbr)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals = 0;
		data->philosophers[i].last_meal_time = get_current_time();
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->ph_nbr);
	if (!data->forks)
		return (1);
	i = -1;
	while (++i < data->ph_nbr)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (1);
		}
	}
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (1);
	data->ph_nbr = (int)cstm_atoi(av[1]);
	data->time_to_die = cstm_atoi(av[2]);
	data->time_to_eat = cstm_atoi(av[3]);
	data->time_to_sleep = cstm_atoi(av[4]);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (1);
	if (init_forks(data))
		return (1);
	if (init_philosophers(data))
	{
		free(data->forks);
		return (1);
	}
	return (0);
}
