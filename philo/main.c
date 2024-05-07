/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:05:33 by lmerveil          #+#    #+#             */
/*   Updated: 2024/05/07 17:09:05 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

//	 av[0]	   av[1]	  av[2]	    av[3]	   av[4]	       av[5]
// ./philo   [#philos]   [#2die]   [#2eat]   [#2sleep]   [#philos must eat]
// 
int main(int ac, char **av)
{
	t_data		data;
	t_table		table;
	t_philo		philos[200];

	if(parse(ac, av))
		return(EXIT_FAILURE);
	init_input(&table, av);
		// printf("ok 1\n");
	init_forks(data.forks, ft_atoi(av[1]));
		// printf("ok 2\n");
	init_philos(philos, &table, &data, data.forks);
		// printf("ok 3\n");
	init_data(table, &data, philos);
		// printf("ok 4\n");
	create_threads(&data); //create/execute threads for each philo
	return(EXIT_SUCCESS);
}
