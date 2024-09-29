/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:02:25 by erian             #+#    #+#             */
/*   Updated: 2024/09/29 13:10:16 by erian            ###   ########.fr       */
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
	{
		printf("Invalid number.\n");
		exit(1);
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result > INT_MAX || result == 0)
	{
		printf("Invalid number.\n");
		exit(1);
	}
	return (result);
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static int	init_philosophers(t_data *data)
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
		data->philosophers[i].last_meal_time = data->start_time;
	}
	return (0);
}

static int	init_forks(t_data *data)
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
	data->start_time = get_current_time();
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = (int)cstm_atoi(av[5]);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
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
