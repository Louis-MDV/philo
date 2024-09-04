/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:05:33 by lmerveil          #+#    #+#             */
/*   Updated: 2024/09/04 17:44:43 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

//		av[0]	   av[1]	  av[2]	    av[3]	   av[4]	       av[5]
// ./philo   [#philos]   [#2die]   [#2eat]   [#2sleep]   [#philos must eat]
//
int	main(int ac, char **av)
{
	t_data	data;
	t_table	table;
	t_philo	philos[200];

	if (parse(ac, av))
		return (EXIT_FAILURE);
	init_input(&table, av);
	init_forks(data.forks, ft_atoi(av[1]));
	init_philos(philos, &table, &data, data.forks);
	init_data(table, &data, philos);
	create_threads(&data);
	return (EXIT_SUCCESS);
}
