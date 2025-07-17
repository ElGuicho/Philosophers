/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:04:37 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/17 20:55:06 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 300

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}				t_philo;

typedef struct s_data
{
	int				dead_flag;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}				t_data;

// Utils
int		ph_strlen(char *str);
int		ph_atoi(const char *str);
void	destroy_mutex(char *str, t_data *data, pthread_mutex_t *forks);
int		ph_usleep(size_t milliseconds);
size_t	get_current_time(void);

// Program initialization
void	init_data(t_data *data, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_phs(t_philo *phs, t_data *data, pthread_mutex_t *forks, char **av);

// Thread functions
int		thread_create(t_data *data, pthread_mutex_t *forks);
int		dead_loop(t_philo *philo);

// Monitor
void	*monitor(void *pointer);
void	print_message(char *str, t_philo *philo, int id);

void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);

#endif