/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:55:02 by erian             #+#    #+#             */
/*   Updated: 2024/09/26 14:39:48 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.c"

static void	assign_forks(t_ph *ph, t_fork *forks, int i)
{
	int	ph_nbr;

	ph_nbr = ph->table->ph_nbr;
	ph->r_fork = &forks[(i + 1) % ph_nbr];
	ph->l_fork = &forks[i];
	if (ph->id % 2)
	{
		ph->r_fork = &forks[i];
		ph->l_fork = &forks[(i + 1) % ph_nbr];
	}
}

static void	ph_init(t_table *table)
{
	int		i;
	t_ph	*ph;

	i = -1;
	while (++i < table->ph_nbr)
	{
		ph = table->phs + i;
		ph->id = i + 1;
		ph->full = 0;
		ph->meal_counter = 0;
		ph->table = table;
		assign_forks(ph, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->time_end = 0;
	table->threads_ready = 0;
	table->phs = malloc(sizeof(t_ph) * table->ph_nbr);
	safe_mutex_handle(table->table_mtx, INIT);
	if (!table->phs)
		exit_error("Philosophers allocation error.\n");
	table->forks = malloc(sizeof(t_fork) * table->ph_nbr);
	if (!table->forks)
		exit_error("Forks allocation error.\n");
	while (++i < table->ph_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	ph_init(table);
}
