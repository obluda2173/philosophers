/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:23:31 by erian             #+#    #+#             */
/*   Updated: 2024/12/30 16:42:40 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	smart_sleep(long long time, t_data *data)
{
	long long	start_time;

	start_time = timestamp();
	while (1)
	{
		pthread_mutex_lock(&(data->meal_check));
		if (!data->not_died)
		{
			pthread_mutex_unlock(&(data->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(data->meal_check));
		if ((timestamp() - start_time) >= time)
			break ;
		usleep(100);
	}
}

void	action_print(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&(data->writing));
	if (data->not_died)
	{
		printf("%lli ", timestamp() - data->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(data->writing));
	return ;
}

void	exit_launcher(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->philos_nbr)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < data->philos_nbr)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->writing));
	pthread_mutex_destroy(&(data->meal_check));
}

bool	socrates(t_data *data)
{
	pthread_mutex_lock(&(data->meal_check));
	if (data->philos_nbr == 1)
	{
		pthread_mutex_unlock(&(data->meal_check));
		smart_sleep(data->time_to_die, data);
		pthread_mutex_lock(&(data->writing));
		printf("%lli %i died\n",
			timestamp() - data->first_timestamp, data->philo[0].id + 1);
		pthread_mutex_unlock(&(data->writing));
		return (false);
	}
	pthread_mutex_unlock(&(data->meal_check));
	return (true);
}
