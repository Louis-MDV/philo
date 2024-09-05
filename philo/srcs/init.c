/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:02:56 by louismdv          #+#    #+#             */
/*   Updated: 2024/09/05 13:40:39 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Initializing user command-line program input
void	init_input(t_table *table, char **av)
{
	table->time_to_die = ft_atoi(av[2]);
	table->time_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->start_time = get_current_time();
	table->num_of_philos = ft_atoi(av[1]);
	if (av[5])
		table->num_times_to_eat = ft_atoi(av[5]);
	else
		table->num_times_to_eat = -1;
}

// Initializing the philosophers individualy in PHILOS struct
void	init_philos(t_philo *philos, t_table *table,
				t_data *data, pthread_mutex_t *forks)
{
	int				i;
	const size_t	current_time = get_current_time();

	i = 0;
	while (i < table->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = current_time;
		philos[i].write_lock = &data->write_lock;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].full = false;
		philos[i].diner_end_flag = &data->diner_end_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0 && table->num_of_philos == 1)
			philos[i].r_fork = NULL;
		else if (i == 0)
			philos[i].r_fork = &forks[table->num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		philos[i].table = *table;
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
void	init_data(t_table table, t_data *data, t_philo *philos)
{
	data->diner_end_flag = false;
	data->philos = philos;
	data->table = table;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

int	parse(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Wrong num of args!\n"), EXIT_FAILURE);
	if (ft_atoi(av[1]) == -1 || ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1)
		return (printf(RED"Num of philosophers invalid!\n"RESET), EXIT_FAILURE);
	if (ft_atoi(av[2]) == -1 || ft_atoi(av[2]) <= 0)
		return (printf(RED"Time to die invalid!\n"RESET), EXIT_FAILURE);
	if (ft_atoi(av[3]) == -1 || ft_atoi(av[3]) <= 0)
		return (printf(RED"Time to eat invalid!\n"RESET), EXIT_FAILURE);
	if (ft_atoi(av[4]) == -1 || ft_atoi(av[4]) <= 0)
		return (printf(RED"Time to sleep invalid!\n"RESET), EXIT_FAILURE);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (printf(RED"Num of times philos must eat invalid!\n"RESET),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
