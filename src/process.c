/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:35:35 by erian             #+#    #+#             */
/*   Updated: 2024/10/01 15:06:06 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	forks_are_free(t_ph *ph, t_ph *ph_arr)
{
	int	result;

	result = -1;
	pthread_mutex_lock(&ph->data->mutex);
	if (ph->id == 0 && !ph[0].forks_taken)
	{
		if ((!ph_arr[1].forks_taken))
			result = 1;
		else if (!ph_arr[ph->data->ph_nbr - 1].forks_taken)
			result = ph->data->ph_nbr - 1;
	}
	else if (!ph->forks_taken && (!ph_arr[ph->id - 1].forks_taken))
		result = ph->id - 1;
	pthread_mutex_unlock(&ph->data->mutex);
	return (result);
}

static int	eat(t_ph *ph, int target_id)
{
	if (ph->meals == ph->data->max_meals || is_dead(ph))
		return (0);
	else
	{
		pthread_mutex_lock(&ph->data->mutex);
		ph->forks_taken = true;
		ph->data->ph_arr[target_id].forks_taken = true;
		print_state(FORK, ph->id + 1, ph);
		pthread_mutex_unlock(&ph->data->mutex);
		print_state(EATING, ph->id + 1, ph);
		ph->meals++;
		cstm_usleep(ph->data->time_to_eat);
		ph->time_last_meal = get_current_time();
		pthread_mutex_lock(&ph->data->mutex);
		ph->forks_taken = false;
		ph->data->ph_arr[target_id].forks_taken = false;
		pthread_mutex_unlock(&ph->data->mutex);
		ph->state = SLEEPING;
		return (1);
	}
	return (1);
}

static int	eating_attempt(t_ph *ph)
{
	ph->target_id = forks_are_free(ph, ph->data->ph_arr);
	if (ph->target_id >= 0
		&& ph->target_id < ph->data->ph_nbr)
	{
		if (!eat(ph, ph->target_id) || is_dead(ph))
			return (0);
		ph->state = SLEEPING;
	}
	if (is_dead(ph))
		return (0);
	return (1);
}

static int	one_philo(t_ph *ph)
{
	if (ph->data->ph_nbr == 1)
	{
		cstm_usleep(ph->data->time_to_die);
		printf("Not enough forks.\nPhilosopher died of starvation.\n");
		return (1);
	}
	return (0);
}

void	*process(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	if (one_philo(ph))
		return (NULL);
	if (ph->id % 2 == 0)
		cstm_usleep(1);
	while (1)
	{
		if (check_death(ph))
			return (NULL);
		if (ph->state == THINKING && (!eating_attempt(ph)))
			return (NULL);
		else if (ph->state == SLEEPING && !is_dead(ph))
		{
			print_state(SLEEPING, ph->id + 1, ph);
			cstm_usleep(ph->data->time_to_sleep);
			if (is_dead(ph))
				return (NULL);
			ph->state = THINKING;
			print_state(THINKING, ph->id + 1, ph);
			cstm_usleep(1);
		}
	}
	return (NULL);
}
