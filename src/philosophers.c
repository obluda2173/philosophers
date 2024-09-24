/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:02:19 by erian             #+#    #+#             */
/*   Updated: 2024/09/24 15:26:24 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	data_init(t_table *table)
{

}

int	main(int ac, char **av)
{
	t_table	table;

	if (!(ac == 5 || ac == 6))
	{
		exit_error("Error input\n");
	}
	parse(av, &table);
	data_init(&table);
	process(&table);
	clean(&table);
}
