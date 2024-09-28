/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:35:35 by erian             #+#    #+#             */
/*   Updated: 2024/09/28 18:23:39 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks_and_eat(t_philosopher *philo, t_data *data)
{
	long	time;

	time = get_current_time() - data->start_time;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->id - 1]);
		printf("%ld %d has taken a fork\n", time, philo->id);
		pthread_mutex_lock(&data->forks[philo->id % data->ph_nbr]);
		printf("%ld %d has taken a fork\n", time, philo->id);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->id % data->ph_nbr]);
		printf("%ld %d has taken a fork\n", time, philo->id);
		pthread_mutex_lock(&data->forks[philo->id - 1]);
		printf("%ld %d has taken a fork\n", time, philo->id);
	}
	printf("%ld %d is eating\n", time, philo->id);
	philo->last_meal_time = get_current_time();
	philo->meals++;
	usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[philo->id % data->ph_nbr]);
	pthread_mutex_unlock(&data->forks[philo->id - 1]);
}

static void	sleep_and_think(t_philosopher *philo, t_data *data)
{
	long	time;

	time = get_current_time() - data->start_time;
	printf("%ld %d is sleeping\n", time, philo->id);
	usleep(data->time_to_sleep);
	printf("%ld %d is thinking\n", time, philo->id);
}

static int	check_death(t_philosopher *philo, t_data *data)
{
	long	time;

	time = get_current_time() - data->start_time;
	if ((time - philo->last_meal_time) > data->time_to_die)
	{
		time = time - data->start_time;
		printf("%ld %d died\n", time, philo->id);
		return (1);
	}
	return (0);
}

static void	handle_single_philo(t_philosopher *philo, t_data *data)
{
	long time = get_current_time() - data->start_time;

	printf("%ld %d has taken a fork\n", time, philo->id);
	usleep(data->time_to_die);
	printf("%ld %d died\n", time, philo->id);
	pthread_exit(NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo_args	*args;
	t_philosopher	*philo;
	t_data			*data;
	long			time;

	args = (t_philo_args *)arg;
	philo = args->philo;
	data = args->data;
	time = get_current_time() - data->start_time;
	if (data->ph_nbr == 1)
		handle_single_philo(philo, data);
	while (1)
	{
		take_forks_and_eat(philo, data);
		if (check_death(philo, data))
			pthread_exit(NULL);
		sleep_and_think(philo, data);
		if (data->max_meals != -1 && philo->meals >= data->max_meals)
			break;
	}
	return (NULL);
}
