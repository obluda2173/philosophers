/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:23:52 by erian             #+#    #+#             */
/*   Updated: 2024/09/26 14:37:12 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	process(void *data)
{
	t_ph	*ph;

	ph = (t_ph *)data;
	wait_all_threads(ph->table);
	return (NULL);
}

void	start(t_table *table)
{
	int	i;

	i = -1;
	if (table->max_meal == 0)
		return ;
	else if (table->ph_nbr == 1)
		;//to do
	else
		while (++i < table->ph_nbr)
			safe_thread_handle(&table->phs[i].thread_id, process, &table->phs[i], CREATE);
}