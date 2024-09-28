/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:02:19 by erian             #+#    #+#             */
/*   Updated: 2024/09/28 10:26:36 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_up(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->ph_nbr)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	free(data->philosophers);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (init_data(&data, ac, av))
		print_exit(NULL, "Error initializing data\n");
	i = -1;
	while (++i < data.ph_nbr)
	{
		if (pthread_create(&data.philosophers[i].thread, NULL, philosopher_routine, &data.philosophers[i]))
		{
			while (--i >= 0)
				pthread_join(data.philosophers[i].thread, NULL);
			print_exit(data, "Error creating thread for philosopher\n");
		}
	}
	i = -1;
	while (++i < data.ph_nbr)
		if (pthread_join(data.philosophers[i].thread, NULL))
			print_exit(data, "Error joining thread for philosopher\n");
	clean_up(&data);
}
