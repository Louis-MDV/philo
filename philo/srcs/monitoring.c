/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:02:46 by louismdv          #+#    #+#             */
/*   Updated: 2024/09/05 13:08:32 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// parallel processes to continuously check that no philo has died
void	*end_monitoring(void *pointer)
{
	t_data	*data;

	data = (t_data *)pointer;
	while (1)
	{
		if (philo_starved_to_death(data) || philos_finished_diner(data))
		{
			if (pthread_mutex_lock(&data->dead_lock) != 0)
				return (perror("pthread_mutex_lock failed"), NULL);
			data->diner_end_flag = true;
			if (pthread_mutex_unlock(&data->dead_lock) != 0)
				return (perror("pthread_mutex_unlock failed"), NULL);
			break ;
		}
	}
	return (pointer);
}

//monitoring death: check if philo died from starvation
int	philo_starved_to_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table.num_of_philos)
	{
		if (pthread_mutex_lock(&data->meal_lock) != 0)
			return (perror("pthread_mutex_lock failed"), -1);
		if (get_current_time() - data->philos[i].last_meal
			>= data->table.time_to_die)
		{
			print_message("died", &data->philos[i], data->philos[i].id);
			if (pthread_mutex_unlock(&data->meal_lock) != 0)
				return (perror("pthread_mutex_unlock failed"), -1);
			return (true);
		}
		if (pthread_mutex_unlock(&data->meal_lock) != 0)
			return (perror("pthread_mutex_unlock failed"), -1);
		i++;
	}
	return (false);
}

//monitoring death: check if all philos are full to finish diner
int	philos_finished_diner(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table.num_of_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (!data->philos[i].full)
		{
			if (pthread_mutex_unlock(&data->meal_lock) != 0)
				return (perror("pthread_mutex_unlock failed"), -1);
			return (false);
		}
		if (pthread_mutex_unlock(&data->meal_lock) != 0)
			return (perror("pthread_mutex_unlock failed"), -1);
		i++;
	}
	return (true);
}
