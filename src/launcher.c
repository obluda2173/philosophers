/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:58:46 by erian             #+#    #+#             */
/*   Updated: 2024/12/26 17:48:22 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	action_print(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
	action_print(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->meal_check));
	action_print(data, philo->id, "is eating");
	philo->last_meal_time = timestamp();
	philo->ate_nbr++;
	pthread_mutex_unlock(&(data->meal_check));
	smart_sleep(data->time_to_eat, data);
	pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
}

static void	*philo_thread(void *void_philo)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)void_philo;
	if (philo->id % 2)
		usleep(100);
	if (philo->data->philos_nbr == 1)
	{
		smart_sleep(philo->data->time_to_die, philo->data);
		printf("Socrates will die :)\n");
		return (NULL);
	}
	while (philo->data->not_died)
	{
		eat(philo);
		if (philo->data->all_ate)
			break ;
		action_print(philo->data, philo->id, "is sleeping");
		smart_sleep(philo->data->time_to_sleep, philo->data);
		action_print(philo->data, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

static void	death_checker(t_data *data, t_philo *philos)
{
	int	i;

	while (!data->all_ate)
	{
		i = -1;
		while (++i < data->philos_nbr && data->not_died)
		{
			pthread_mutex_lock(&(data->meal_check));
			if (td(philos[i].last_meal_time, timestamp()) > data->time_to_die)
			{
				action_print(data, philos[i].id, "died");
				data->not_died = false;
			}
			pthread_mutex_unlock(&(data->meal_check));
			usleep(100);
		}
		if (!data->not_died)
			break ;
		i = 0;
		while (data->must_eat_nbr != -1 && i < data->philos_nbr
			&& philos[i].ate_nbr >= data->must_eat_nbr)
			i++;
		if (i == data->philos_nbr)
			data->all_ate = true;
	}
}

static void	exit_launcher(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->philos_nbr)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < data->philos_nbr)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->writing));
}

bool	launcher(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = data->philo;
	data->first_timestamp = timestamp();
	while (++i < data->philos_nbr)
	{
		if (pthread_create(&(philo[i].thread_id),
				NULL, philo_thread, &(philo[i])))
			return (true);
		philo[i].last_meal_time = timestamp();
	}
	death_checker(data, data->philo);
	exit_launcher(data, philo);
	return (false);
}
