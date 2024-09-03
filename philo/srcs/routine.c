/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:59:29 by louismdv          #+#    #+#             */
/*   Updated: 2024/09/03 23:32:41 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (*(philo->diner_end_flag) != true)
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

void	eat(t_philo *philo)
{
	if (*(philo->diner_end_flag) != true)
		return ;
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return ;
	print_message("has taken left fork", philo, philo->id);
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return ;
	print_message("has taken right fork", philo, philo->id);
	
	if (pthread_mutex_lock(philo->meal_lock) != 0)
		return ;
	philo->eating = true;
	
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->table.time_to_eat);
	
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table.num_times_to_eat	&& philo->full == false)
		philo->full = true;
	philo->last_meal = get_current_time();
	if (pthread_mutex_unlock(philo->meal_lock) != 0)
		return ;
	
	printf(YELLOW"[%d] [%d] count meals for [philo %d]\n"RESET, philo->meals_eaten, philo->full, philo->id);
	
	philo->eating = false;
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return ;
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return ;
}

// Dream routine funtion
void	dream(t_philo *philo)
{
	if (*(philo->diner_end_flag) != true)
		return ;
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->table.time_to_sleep);
}

// Think routine funtion
void	think(t_philo *philo)
{
	if (*(philo->diner_end_flag) != true)
		return ;
	print_message("is thinking", philo, philo->id);
}

// // check if passed philo is dead
// int	check_if_philo_dead(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->dead_lock);
// 	if (philo->dead == true)
// 		return (pthread_mutex_unlock(philo->dead_lock), true);
// 	return (pthread_mutex_unlock(philo->dead_lock), false);
// }
