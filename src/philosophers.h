/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:03:28 by erian             #+#    #+#             */
/*   Updated: 2024/09/28 10:18:24 by erian            ###   ########.fr       */
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
#include <errno.h>

void	print_return(char *str);
void	print_exit(t_data *data, char *str);
void	clean_up(t_data *data);
int		main(int ac, char **av);

typedef	struct	s_philosopher
{
	int			id;
	int			meals;
	long		last_meal_time;
	pthread_t	thread;
}				t_philosopher;

typedef struct		s_data
{
	int				ph_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;	
}					t_data;


#endif