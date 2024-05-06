/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:05:33 by lmerveil          #+#    #+#             */
/*   Updated: 2024/05/06 18:57:14 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

//	 av[0]	   av[1]	  av[2]	    av[3]	   av[4]	       av[5]
// ./philo   [#philos]   [#2die]   [#2eat]   [#2sleep]   [#philos must eat]

int main(int ac, char **av)
{
	t_data		data;
	t_table		table;
	
	if(parse(ac, av))
		return(EXIT_FAILURE);
	init_input(&table, av);
	init_forks(data.forks, ft_atoi(av[1]));
	init_philos(data.philos, &data, data.forks, av);
	init_program(table, &data, data.philos);

	create_threads(&data); //create/execute threads for each philo
	
	return(EXIT_SUCCESS);
}
