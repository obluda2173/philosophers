/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:02:25 by erian             #+#    #+#             */
/*   Updated: 2024/10/01 17:55:41 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	cstm_atoi(const char *str, t_data *data)
{
	long	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		print_free_exit("Invalid number.\n", data);
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	if (result > INT_MAX || result == 0)
		print_free_exit("Invalid number.\n", data);
	return (result);
}

int	init_data(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
	{
		printf("Wrong amount of arguments.\n");
		return (0);
	}
	data->ph_nbr = (int)cstm_atoi(av[1], data);
	data->time_to_die = (size_t)cstm_atoi(av[2], data);
	data->time_to_eat = (size_t)cstm_atoi(av[3], data);
	data->time_to_sleep = (size_t)cstm_atoi(av[4], data);
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = (int)cstm_atoi(av[1], data);
	data->all_alive = true;
	data->time_begin = get_current_time();
	return (1);
}

void	switch_mutex(t_data *data, bool state)
{
	int	error_1;
	int	error_2;

	error_1 = 0;
	if (state == false)
	{
		error_1 = pthread_mutex_destroy(&data->mutex);
		error_2 = pthread_mutex_destroy(&data->write);
	}
	else if (state == true)
	{
		error_1 = pthread_mutex_init(&data->mutex, NULL);
		error_2 = pthread_mutex_init(&data->write, NULL);
	}
	if (error_1 != 0 || error_2 != 0)
		printf("Mutex error\n");
}

void	create_threads(t_data *data, t_ph *phs)
{
	int	i;

	i = -1;
	while (++i < data->ph_nbr)
	{
		phs[i].id = i;
		phs[i].data = data;
		phs[i].state = 3;
		pthread_mutex_lock(&data->mutex);
		phs[i].forks_taken = false;
		pthread_mutex_unlock(&data->mutex);
		phs[i].meals = 0;
		phs[i].time_last_meal = data->time_begin;
		if (pthread_create(&phs[i].thread, NULL, process, &phs[i]) != 0)
			printf("Error creating a thread.\n");
	}
}

void	join_threads(t_data *data, t_ph *phs)
{
	int	i;

	i = -1;
	while (++i < data->ph_nbr)
		if (pthread_join(phs[i].thread, NULL) != 0)
			printf("Error joining a thread.\n");
}
