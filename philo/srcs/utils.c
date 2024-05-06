/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:45:45 by lmerveil          #+#    #+#             */
/*   Updated: 2024/05/06 16:52:53 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//print status message function if philo not dead
void    print_message(char *status, t_philo  *philo, int id)
{
    size_t time;

    pthread_mutex_lock(philo->write_lock);
    time = get_current_time() - philo->table.start_time;
    if (!check_if_philo_dead(philo))
        printf("%zu %d %s\n", time, id, status);
    pthread_mutex_unlock(philo->write_lock);
}

int ft_strlen(const char *str)
{
	int len;

	len = 0;
	while(str[len])
		len++;
	return (len);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	sign;

	sign = 1;
	i = 0;
	nb = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		return(printf("sign invalid: "), -1);
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10;
		nb = nb + (nptr[i] - '0');
		i++;
	}
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
			i++;
	if (i == ft_strlen(nptr))
		return (nb);
	return (printf("not digits: "), -1);
}

//versio usleep to avoid sleeping to long
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

//returns current time of day in milliseconds
size_t	get_current_time(void)
{
	struct timeval	tp; //tp = timepointer

	if (gettimeofday(&tp, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}
//  struct timeval
//{
//   	time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
//      suseconds_t  tv_usec;  /* and microseconds */
// };