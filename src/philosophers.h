/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:03:28 by erian             #+#    #+#             */
/*   Updated: 2024/10/01 11:49:56 by erian            ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef struct s_ph
{
	int			id;
	int			state;
	int			meals;
	int			target_id;
	bool		forks_taken;
	size_t		time_last_meal;
	pthread_t	thread;
	t_data		*data;
}				t_ph;

typedef enum e_types
{
	EATING		=	1,
	SLEEPING	=	2,
	THINKING	=	3,
	DEAD		=	4,
	FORK		=	5,
}				t_types;

typedef struct s_data
{
	int				ph_nbr;
	int				max_meals;
	unsigned long	exec_usec;
	bool			all_alive;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_begin;
	t_ph			*ph_arr;
	pthread_mutex_t	mutex;
	pthread_mutex_t	write;
}					t_data;

/* 
**	utils.c 
*/
size_t	get_current_time(void);
int		check_death(t_ph *ph);
int		is_dead(t_ph *ph);
void	cstm_usleep(size_t ms);
/* 
**	process.c 
*/
void	*process(void *arg);
/* 
**	init.c 
*/
int		init_data(int ac, char **av, t_data *data);
void	switch_mutex(t_data *data, bool state);
void	create_threads(t_data *data, t_ph *phs);
void	join_threads(t_data *data, t_ph *phs);
/* 
**	philosophers.c 
*/
void	print_free_exit(char *str, t_data *data);
void	print_state(int state, int index, t_ph *ph);
int		main(int ac, char **av);

#endif