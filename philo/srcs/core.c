/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:02:46 by louismdv          #+#    #+#             */
/*   Updated: 2024/05/06 16:34:37 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// parallel processes to continuously check that no philo has died
void *end_monitoring(void *pointer)
{
    t_data *data;

    data = (t_data *)pointer;
    while (1)
    {
        if (philo_starved_to_death(data) || philos_finished_diner(data))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->diner_end_flag = true;
			pthread_mutex_unlock(&data->dead_lock);
			break;
		}
    }
    return(pointer);
}

//monitoring death: check if philo died from starvation
int philo_starved_to_death(t_data *data)
{
    int i;
    
    i = 1;
    while (i <= data->table.num_of_philos)
    {
        pthread_mutex_lock(&data->meal_lock);
        if (get_current_time() - data->philos[i].last_meal >= data->table.time_to_die && !data->philos[i].eating)
		{
			print_message("died", &data->philos[i], data->philos[i].id);
            return (pthread_mutex_unlock(&data->meal_lock), EXIT_FAILURE);
		}
		i++;
    }
    return (pthread_mutex_unlock(&data->meal_lock), EXIT_SUCCESS);
}

//monitoring death: check if all philos are full to finish diner
int philos_finished_diner(t_data *data)
{
    int i;

    i = 1;
    while (i <= data->table.num_of_philos)
    {
		pthread_mutex_lock(&data->meal_lock);
        if (!data->philos[i].full)
            return (pthread_mutex_unlock(&data->meal_lock), EXIT_SUCCESS);
        i++;
    }
    return (pthread_mutex_unlock(&data->meal_lock), EXIT_FAILURE);
}
