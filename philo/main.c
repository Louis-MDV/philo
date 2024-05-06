/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:05:33 by lmerveil          #+#    #+#             */
/*   Updated: 2024/05/06 13:34:59 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

//	 av[0]	   av[1]	  av[2]	    av[3]	   av[4]	       av[5]
// ./philo   [#philos]   [#2die]   [#2eat]   [#2sleep]   [#philos must eat]

//struct prgram -- has dead flag, philos stuct pointer, mutex pointers
// 		-> used to access data

//struct philos -- used to init philos


int main(int ac, char **av)
{
	pthread_mutex_t forks[200];
	t_philo			philos[200];
	t_data			data;
	t_table			table;
	
	if(parse(ac, av) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	init_input(&table, av);
	init_forks(forks, ft_atoi(av[1]));
	init_philos(philos, &data, forks, av);
	init_program(table, &data, philos);

	create_threads(&data); //create/execute threads for each philo
	
	return(EXIT_SUCCESS);
}
