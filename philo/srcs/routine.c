/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:59:29 by louismdv          #+#    #+#             */
/*   Updated: 2024/05/06 13:16:27 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *pointer)
{
	t_philo	*philo;
	
	philo = (t_philo *)pointer;
	eat(philo);
	dream(philo);
	think(philo);
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
   	if(pthread_mutex_lock(philo->l_fork) != 0)
		pthread_mutex_unlock(philo->l_fork);
	print_message("has taken left fork", philo, philo->id);
	if(pthread_mutex_lock(philo->r_fork) != 0);
		pthread_mutex_unlock(philo->r_fork);
	print_message("has taken left fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->table.time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
