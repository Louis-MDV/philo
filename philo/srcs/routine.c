/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:59:29 by louismdv          #+#    #+#             */
/*   Updated: 2024/05/06 16:51:02 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *pointer)
{
	t_philo	*philo;
	
	philo = (t_philo *)pointer;
	while (!check_if_philo_dead(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return(pointer);
}

// Think routine funtion
void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

// Dream routine funtion
void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->table.time_to_sleep);
}

void    eat(t_philo *philo)
{
   	pthread_mutex_lock(philo->l_fork);
	print_message("has taken left fork", philo, philo->id);
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken left fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->table.time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table.num_times_to_eat && !(philo->full))
		philo->full = 1;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

// check if passed philo is dead
int check_if_philo_dead(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    if (*philo->end == true)
        return (pthread_mutex_unlock(philo->dead_lock), EXIT_SUCCESS);
    return(pthread_mutex_unlock(philo->dead_lock), EXIT_FAILURE);
}
