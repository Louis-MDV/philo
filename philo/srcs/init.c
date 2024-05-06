/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:02:56 by louismdv          #+#    #+#             */
/*   Updated: 2024/05/06 16:34:51 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Initializing user command-line program input
void	init_input(t_table *table, char **av)
{
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->start_time = get_current_time();			//time started the program
	table->num_of_philos = ft_atoi(av[1]);
	if (av[5])
		table->num_times_to_eat = ft_atoi(av[5]);
	else
		table->num_times_to_eat = -1;
}

// Initializing the philosophers individualy in PHILOS struct
void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 1;
	while (i <= ft_atoi(av[1]))
	{
		philos[i].id = i;							//philo number
		philos[i].eating = 0;						//eating status. 1 if eating
		philos[i].meals_eaten = 0; 					//eaten meals
		philos[i].last_meal = get_current_time();	//time ate last meal
		philos[i].write_lock = &data->write_lock;	//stdout writing lock
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;		//philo eating
		philos[i].end = &data->diner_end_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[(data->table.num_of_philos) - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		philos[i].table = data->table;
		i++;
	}
}

// Initializing the forks mutexes
void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

// Initializing the PROGRAM structure
void	init_program(t_table table, t_data *data, t_philo *philos)
{
	data->diner_end_flag = false;		//flag to use in case a philo dies / all philos are full
	data->philos = philos;			//pointer to the whole philos struct. Enabling access to indiv level data
	data->table = table;
	pthread_mutex_init(&data->write_lock, NULL); //init write mutex
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

int parse(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return(printf("Wrong num of args!\n"), EXIT_FAILURE);
	if (ft_atoi(av[1]) == -1 || ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1)
		return(printf(RED"Num of philosophers invalid!\n"RESET), EXIT_FAILURE);
	if (ft_atoi(av[2]) == -1 || ft_atoi(av[2]) <= 0)
		return(printf(RED"Time to die invalid!\n"RESET), EXIT_FAILURE);
	if (ft_atoi(av[3]) == -1 || ft_atoi(av[3]) <= 0)
		return(printf(RED"Time to eat invalid!\n"RESET), EXIT_FAILURE);
	if (ft_atoi(av[4]) == -1 || ft_atoi(av[4]) <= 0)
		return(printf(RED"Time to sleep invalid!\n"RESET), EXIT_FAILURE);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return(printf(RED"Num of times philos must eat invalid!\n"RESET), EXIT_FAILURE);
	return(EXIT_SUCCESS);
}
