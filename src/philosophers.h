/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:03:28 by erian             #+#    #+#             */
/*   Updated: 2024/09/24 15:25:54 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

void	parse(char **av, t_table *table);

typedef pthread_mutex_t t_mutex;
typedef struct	s_table	t_table;

typedef struct	s_fork
{
	t_mutex fork;
	int		fork_id;
	
}			t_fork;

typedef struct	s_ph
{
	int			id;
	long		meal_counter;
	int			full;
	long		last_meal_time;
	t_fork		*l_fork;
	t_fork		*r_fork;
	pthread_t	thread_id;
	t_table		*table;
}				t_ph;

struct			s_table
{
	long		ph_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		max_meal;
	long		time_start;
	int			time_end;
	t_fork		*forks;
	t_ph		*phs;	
};

#endif