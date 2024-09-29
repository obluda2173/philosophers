/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:03:28 by erian             #+#    #+#             */
/*   Updated: 2024/09/29 17:25:55 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>

typedef struct s_philosopher
{
	int			id;
	int			meals;
	long		last_meal_time;
	pthread_t	thread;
}				t_philosopher;

typedef struct s_data
{
	int				ph_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				max_meals;
	long			start_time;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
	pthread_mutex_t meal_mutex;
}					t_data;

typedef struct s_philo_args
{
	t_philosopher	*philo;
	t_data			*data;
}					t_philo_args;

void	print_return(char *str);
void	*philosopher_routine(void *arg);
long	get_current_time(void);
int		init_data(t_data *data, int ac, char **av);
void 	smart_usleep(t_philosopher *philo, t_data *data, long duration);
void	clean_up(t_data *data);
int		main(int ac, char **av);

#endif