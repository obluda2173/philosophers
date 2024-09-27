/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:02:19 by erian             #+#    #+#             */
/*   Updated: 2024/09/27 18:00:35 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clean_up(t_data *data)
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
		print_return("Error initializing data\n");
	i = -1;
	while (++i < data.ph_nbr)
	{
		if (pthread_create(&data.philosophers[i].thread, NULL, philosopher_routine, &data.philosophers[i]))
		{
			printf("Error creating thread for philosopher %d\n", i + 1);
			return (1);
		}
	}
	i = -1;
	while (++i < data.ph_nbr)
	{
		if (pthread_join(data.philosophers[i].thread, NULL))
		{
			printf("Error joining thread for philosopher %d\n", i + 1);
			return (1);
		}
	}
	clean_up(&data);
}
