/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:54:22 by erian             #+#    #+#             */
/*   Updated: 2024/12/30 16:42:01 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	cstm_atoi(const char *str)
{
	long	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		printf("Invalid arguments");
		exit(1);
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	if (result > INT_MAX || result == 0)
	{
		printf("Invalid arguments");
		exit(1);
	}
	return ((int)result);
}

static void	init_mutex(t_data *data)
{
	int	i;

	i = data->philos_nbr;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
		{
			printf("Error while initialising mutex");
			exit(1);
		}
	}
	if (pthread_mutex_init(&(data->writing), NULL)
		|| pthread_mutex_init(&(data->meal_check), NULL))
	{
		printf("Error while initialising mutex");
		exit(1);
	}
}

static int	init_philos(t_data *data)
{
	int	i;

	i = data->philos_nbr;
	while (--i >= 0)
	{
		data->philo[i].id = i;
		data->philo[i].ate_nbr = 0;
		data->philo[i].left_fork_id = i;
		data->philo[i].right_fork_id = (i + 1) % data->philos_nbr;
		data->philo[i].last_meal_time = 0;
		data->philo[i].data = data;
	}
	return (0);
}

static void	parse(t_data *data, int ac, char **av)
{
	data->philos_nbr = cstm_atoi(av[1]);
	data->time_to_die = cstm_atoi(av[2]);
	data->time_to_eat = cstm_atoi(av[3]);
	data->time_to_sleep = cstm_atoi(av[4]);
	data->all_ate = false;
	data->not_died = true;
	if (ac == 6)
		data->must_eat_nbr = cstm_atoi(av[5]);
	else
		data->must_eat_nbr = -1;
	if (data->philos_nbr > 200 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
	{
		printf("Invalid arguments");
		exit(1);
	}
	init_mutex(data);
	init_philos(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf("Wrong amount of arguments\n"), 0);
	parse(&data, ac, av);
	if (launcher(&data))
		return (printf("Error creating the threads\n"), 0);
	return (0);
}
