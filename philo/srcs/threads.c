/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 23:20:09 by louismdv          #+#    #+#             */
/*   Updated: 2024/09/04 17:44:21 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_threads(t_data *data)
{
	int			i;
	pthread_t	monitoring;

	if (pthread_create(&monitoring, NULL, &end_monitoring, data) != 0)
		return (destroy_threads(data), printf("pthread create error: monitoring "), EXIT_FAILURE);
	i = 0;
	while (i < data->table.num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]) != 0)
			return (destroy_threads(data), print_message("pthread_create error: ", data->philos, data->philos[i].id), EXIT_FAILURE);
		i++;
	}
	join_philo_threads(data, monitoring);
	return (0);
}

void	join_philo_threads(t_data *data, pthread_t monitoring)
{
	int i;

	if (pthread_join(monitoring, NULL) != 0)
		destroy_threads(data);
	i = 0;
	while (i < data->table.num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy_threads(data);
		i++;
	}
	destroy_threads(data);
	return ;
}

void	destroy_threads(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);

	i = 0;
	while (i < data->table.num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
