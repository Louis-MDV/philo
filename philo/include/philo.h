/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:23:48 by lmerveil          #+#    #+#             */
/*   Updated: 2024/09/05 13:45:38 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"

//		av[0]	   av[1]	  av[2]	    av[3]	   av[4]	       av[5]
// ./philo   [#philos]   [#2die]   [#2eat]   [#2sleep]   [#philos must eat]

typedef pthread_mutex_t	t_mtx;

// common command line data
typedef struct s_table
{
	size_t				time_to_die;
	size_t				time_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	int					num_of_philos;
	int					num_times_to_eat;
}						t_table;

// philo individual data
typedef struct s_philo
{
	pthread_t			thread;				// a philo is a thread
	int					id;
	bool				eating;
	int					meals_eaten;
	bool				full;
	bool				*diner_end_flag;

	size_t				last_meal;
	t_mtx				*r_fork;
	t_mtx				*l_fork;
	t_mtx				*write_lock;		// lock when writing to stdout
	t_mtx				*dead_lock;			// lock when changing the death flag
	t_mtx				*meal_lock;			// lock when eating
	t_table				table;
}						t_philo;

// all data united
typedef struct s_data
{
	bool				diner_end_flag;
	t_mtx				dead_lock;
	t_mtx				meal_lock;
	t_mtx				write_lock;
	t_mtx				forks[200];
	t_philo				*philos;			// data related to given philo[i]
	t_table				table;				// data related to passed command
}						t_data;

// initiation
void					init_philos(t_philo *philos, t_table *table,
							t_data *data, pthread_mutex_t *forks);
void					init_forks(pthread_mutex_t *forks, int philo_num);
void					init_input(t_table *table, char **argv);
void					init_data(t_table table, t_data *data, t_philo *philos);

// utils
int						ft_atoi(const char *nptr);
int						ft_strlen(const char *str);
size_t					get_current_time(void);
void					print_message(char *status, t_philo *philos, int id);
int						ft_usleep(size_t milliseconds);
int						diner_finished(t_philo *philo);
void					solo_philo(t_philo *philo);
void					lock_mutex(t_mtx *mutex1, t_mtx *mutex2, t_mtx *mutex3);

// dead monitoring
int						philo_starved_to_death(t_data *data);
int						philos_finished_diner(t_data *data);

// thread functions
void					*routine(void *pointer);
void					*end_monitoring(void *pointer);

// core functions
int						parse(int ac, char **av);
int						create_threads(t_data *data);

// exiting
void					join_philo_threads(t_data *data, pthread_t monitoring);
void					destroy_threads(t_data *data);

// routine
void					think(t_philo *philo);
void					dream(t_philo *philo);	// sleep already taken
void					eat(t_philo *philo);

#endif // PHILO_H