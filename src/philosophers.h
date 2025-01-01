/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:43:54 by erian             #+#    #+#             */
/*   Updated: 2024/12/30 15:46:04 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				ate_nbr;
	int				left_fork_id;
	int				right_fork_id;
	long long		last_meal_time;
	pthread_t		thread_id;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philos_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_nbr;
	bool			all_ate;
	bool			not_died;
	t_philo			philo[250];
	long long		first_timestamp;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
}					t_data;

int			main(int ac, char **av);

bool		launcher(t_data *data);

long long	timestamp(void);
void		smart_sleep(long long time, t_data *data);
void		action_print(t_data *data, int id, char *str);
void		exit_launcher(t_data *data, t_philo *philos);
bool		socrates(t_data *data);

#endif