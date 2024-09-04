/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:59:29 by louismdv          #+#    #+#             */
/*   Updated: 2024/09/04 17:52:51 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (diner_finished(philo) == false)
	{
		eat(philo);
		if (diner_finished(philo) == true)
			break ;
		dream(philo);
		if (diner_finished(philo) == true)
			break ;
		think(philo);
		if (diner_finished(philo) == true)
			break ;
	}
	return (pointer);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (diner_finished(philo) == true)
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	print_message("has taken left fork", philo, philo->id);
	if (philo->r_fork == NULL)
	{
		while (1)
		{
			if (diner_finished(philo) == true)
				return ;
			usleep(200);
		}
	}
	pthread_mutex_lock(philo->r_fork);
	if (diner_finished(philo) == true)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	print_message("has taken right fork", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	if (diner_finished(philo) == true)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->meal_lock);
		return ;
	}
	print_message("is eating", philo, philo->id);
	philo->last_meal = get_current_time();
	if (diner_finished(philo) == true)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->meal_lock);
		return ;
	}
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table.num_times_to_eat
		&& philo->full == false)
		philo->full = true;
	if (pthread_mutex_unlock(philo->meal_lock) != 0)
		return ;
	ft_usleep(philo->table.time_to_eat);
	printf(YELLOW "eaten_meals: [%d] full:[%d] for [philo %d]\n" RESET,
		philo->meals_eaten, philo->full, philo->id);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return ;
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return ;
}

// Dream routine funtion
void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->table.time_to_sleep);
}

// Think routine funtion
void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

// check if passed philo is dead
int	diner_finished(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->diner_end_flag) == true)
		return (pthread_mutex_unlock(philo->dead_lock), true);
	return (pthread_mutex_unlock(philo->dead_lock), false);
}
