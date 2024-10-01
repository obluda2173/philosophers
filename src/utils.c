/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:10:02 by erian             #+#    #+#             */
/*   Updated: 2024/10/01 15:06:32 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	cstm_usleep(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(ms);
}

int	is_dead(t_ph *ph)
{
	if ((get_current_time() - ph->time_last_meal) > ph->data->time_to_die)
	{
		pthread_mutex_lock(&ph->data->mutex);
		print_state(DEAD, ph->id + 1, ph);
		ph->data->all_alive = false;
		pthread_mutex_unlock(&ph->data->mutex);
		return (1);
	}
	return (0);
}

int	check_death(t_ph *ph)
{
	pthread_mutex_lock(&ph->data->mutex);
	if (!ph->data->all_alive)
	{
		pthread_mutex_unlock(&ph->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->mutex);
	return (0);
}
