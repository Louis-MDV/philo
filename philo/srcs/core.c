/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:02:46 by louismdv          #+#    #+#             */
/*   Updated: 2024/05/06 13:33:10 by louismdv         ###   ########.fr       */
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
            break;
    }
    return(pointer);
}

// check if passed philo is dead
int check_if_philo_dead(t_philo *philos)
{
    pthread_mutex_lock(philos->dead_lock);
    if (philos->dead == 1)
        return (pthread_mutex_unlock(philos->dead_lock), 1);
    return(pthread_mutex_unlock(philos->dead_lock), 0);
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
            return(print_message("died", data, data->philos[i].id), pthread_mutex_unlock(&data->meal_lock), 1);
        i++;
    }
    return(pthread_mutex_unlock(&data->meal_lock), 0);
}

//monitoring death: check if all philos are full to finish diner
int philos_finished_diner(t_data *data)
{
    int i;

    i = 1;
    while (i <= data->table.num_of_philos)
    {
        if (!data->philos[i].full);
            return (0);
        i++;
    }
    return (1);
}
