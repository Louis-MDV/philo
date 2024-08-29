/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:59:29 by louismdv          #+#    #+#             */
/*   Updated: 2024/08/29 18:36:10 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (check_if_philo_dead(philo) == false)
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	printf(RED "locked l_fork\n" RESET);
	print_message("has taken left fork", philo, philo->id);
	pthread_mutex_lock(philo->r_fork);
	printf(RED "locked r_fork\n" RESET);
	print_message("has taken right fork", philo, philo->id);
	philo->eating = true;
	
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->table.time_to_eat);
	
	// pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table.num_times_to_eat
		&& philo->full == false)
		philo->full = true;
	philo->last_meal = get_current_time();
	// pthread_mutex_unlock(philo->meal_lock);
	printf("meals\n");
	
	printf(GREEN "unlocked meal_lock\n" RESET);
	philo->eating = false;
	pthread_mutex_unlock(philo->l_fork);
	printf(GREEN "unlocked l_fork\n" RESET);
	pthread_mutex_unlock(philo->r_fork);
	printf(GREEN "unlocked r_fork\n" RESET);
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
int	check_if_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->end == true)
		return (pthread_mutex_unlock(philo->dead_lock), true);
	return (pthread_mutex_unlock(philo->dead_lock), false);
}
