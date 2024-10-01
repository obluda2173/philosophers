/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:02:19 by erian             #+#    #+#             */
/*   Updated: 2024/10/01 17:58:40 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_free_exit(char *str, t_data *data)
{
	printf("%s", str);
	free(data);
	exit(1);
}

void	print_state(int state, int index, t_ph *ph)
{
	size_t	time;

	pthread_mutex_lock(&ph->data->write);
	time = get_current_time() - ph->data->time_begin;
	if (ph->data->all_alive)
	{
		if (state == EATING)
			printf("%zu %i is eating\n", time, index);
		else if (state == SLEEPING)
			printf("%zu %i is sleeping\n", time, index);
		else if (state == THINKING)
			printf("%zu %i is thinking\n", time, index);
		else if (state == FORK)
			printf("%zu %i has taken fork\n", time, index);
		else if (state == DEAD)
			printf("%zu %i is dead\n", time, index);
		else if (state == 0)
			printf("State is not assigned\n");
	}
	pthread_mutex_unlock(&ph->data->write);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		print_free_exit("Memory allocation error.\n", NULL);
	if (init_data(ac, av, data))
	{
		data->ph_arr = (t_ph *)malloc(sizeof(t_ph));
		if (!data->ph_arr)
			print_free_exit("Memory allocation error.\n", data);
		switch_mutex(data, true);
		create_threads(data, data->ph_arr);
		join_threads(data, data->ph_arr);
		switch_mutex(data, false);
		free(data->ph_arr);
	}
	free(data);
	return (0);
}
