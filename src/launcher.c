/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:58:46 by erian             #+#    #+#             */
/*   Updated: 2024/12/30 16:41:44 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->philos_nbr == 1)
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
		pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
	}
	else
	{
		pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
		pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	}
	action_print(data, philo->id, "has taken a fork");
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

static void	check_death(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->meal_check));
	if ((timestamp() - philo->last_meal_time) > data->time_to_die
		&& data->not_died)
	{
		pthread_mutex_lock(&(data->writing));
		data->not_died = false;
		printf("%lli %i died\n",
			timestamp() - data->first_timestamp, philo->id + 1);
		pthread_mutex_unlock(&(data->writing));
	}
	pthread_mutex_unlock(&(data->meal_check));
}

static void	check_meal_count(t_philo *philo)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = philo->data;
	if (data->must_eat_nbr == -1)
		return ;
	pthread_mutex_lock(&(data->meal_check));
	all_ate = 1;
	i = -1;
	while (++i < data->philos_nbr)
	{
		if (data->philo[i].ate_nbr < data->must_eat_nbr)
		{
			all_ate = 0;
			break ;
		}
	}
	if (all_ate)
		data->all_ate = true;
	pthread_mutex_unlock(&(data->meal_check));
}

static void	*philo_thread(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->id % 2)
		usleep(100);
	while (1 && socrates(philo->data))
	{
		pthread_mutex_lock(&(philo->data->meal_check));
		if (!philo->data->not_died || philo->data->all_ate)
		{
			pthread_mutex_unlock(&(philo->data->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(philo->data->meal_check));
		eat(philo);
		check_meal_count(philo);
		pthread_mutex_lock(&(philo->data->meal_check));
		action_print(philo->data, philo->id, "is sleeping");
		pthread_mutex_unlock(&(philo->data->meal_check));
		smart_sleep(philo->data->time_to_sleep, philo->data);
		action_print(philo->data, philo->id, "is thinking");
		check_death(philo);
	}
	return (NULL);
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
		pthread_mutex_lock(&(data->meal_check));
		philo[i].last_meal_time = timestamp();
		pthread_mutex_unlock(&(data->meal_check));
		if (pthread_create(&(philo[i].thread_id),
				NULL, philo_thread, &(philo[i])))
			return (true);
	}
	exit_launcher(data, philo);
	return (false);
}
