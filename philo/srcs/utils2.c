/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:44:38 by louismdv          #+#    #+#             */
/*   Updated: 2024/09/05 13:45:04 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	solo_philo(t_philo *philo)
{
	while (1)
	{
		if (diner_finished(philo))
			return ;
		usleep(200);
	}
}

void	lock_mutex(t_mtx *mutex1, t_mtx *mutex2, t_mtx *mutex3)
{
	if (mutex1 != NULL)
		pthread_mutex_unlock(mutex1);
	if (mutex2 != NULL)
		pthread_mutex_unlock(mutex2);
	if (mutex3 != NULL)
		pthread_mutex_unlock(mutex3);
}
