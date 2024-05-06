/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 23:20:09 by louismdv          #+#    #+#             */
/*   Updated: 2024/05/06 13:51:19 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


int create_threads(t_data *data)
{
    int i;
    pthread_t   monitoring;
    
    if (pthread_create(&monitoring, NULL, &end_monitoring, &data) != 0)
        return(printf("pthread create error!"), 1);
    i = 1;
    while (i <= data->table.num_of_philos) 
    {
        if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]) != 0)
            return (printf("pthread_create error"), 1);
        i++;
    }
    i = 0;
    if(pthread_join(monitoring, NULL) != 0)
        destroy_threads(data);
    //join and destroy created threads
}

void    destroy_threads(t_data *data)
{
    pthread_mutex_destroy(&data->dead_lock);
    pthread_mutex_destroy(&data->meal_lock);
    pthread_mutex_destroy(&data->write_lock);
    
    pthread_mutex_destroy(&data->philo.l_fork);
    
}