/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:02:19 by erian             #+#    #+#             */
/*   Updated: 2024/09/28 18:25:37 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_exit(t_data *data, char *str)
{
	printf("%s", str);
	if (data)
		clean_up(data);
	exit(1);
}

void	clean_up(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->ph_nbr)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	free(data->philosophers);
}

static int	create_threads(t_data *data, t_philo_args *philo_args)
{
	int	i;

	i = -1;
	while (++i < data->ph_nbr)
	{
		philo_args[i].philo = &data->philosophers[i];
		philo_args[i].data = data;
		if (pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &philo_args[i]))
		{
			while (--i >= 0)
				pthread_join(data->philosophers[i].thread, NULL);
			return (1);
		}
	}
	return (0);
}

static int	join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->ph_nbr)
		if (pthread_join(data->philosophers[i].thread, NULL))
			return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo_args	*philo_args;

	if (init_data(&data, ac, av))
		print_exit(NULL, "Error initializing data.\n");
	philo_args = malloc(sizeof(t_philo_args) * data.ph_nbr);
	if (!philo_args)
		print_exit(&data, "Error allocating memory\n");
	if (create_threads(&data, philo_args))
		print_exit(&data, "Error creating thread for philosopher\n");
	if (join_threads(&data))
		print_exit(&data, "Error joining thread for philosopher\n");
	clean_up(&data);
	free(philo_args);
	return (0);
}
