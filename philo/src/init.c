/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:47:04 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/17 20:51:48 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_input(t_philo *philo, char **av)
{
	philo->num_of_philos = ph_atoi(av[1]);
	philo->time_to_die = ph_atoi(av[2]);
	philo->time_to_eat = ph_atoi(av[3]);
	philo->time_to_sleep = ph_atoi(av[4]);
	if (av[5])
		philo->num_times_to_eat = ph_atoi(av[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_phs(t_philo *phs, t_data *data, pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 0;
	while (i < ph_atoi(av[1]))
	{
		phs[i].id = i + 1;
		phs[i].eating = 0;
		phs[i].meals_eaten = 0;
		init_input(&phs[i], av);
		phs[i].start_time = get_current_time();
		phs[i].last_meal = get_current_time();
		phs[i].write_lock = &data->write_lock;
		phs[i].dead_lock = &data->dead_lock;
		phs[i].meal_lock = &data->meal_lock;
		phs[i].dead = &data->dead_flag;
		phs[i].l_fork = &forks[i];
		if (i == 0)
			phs[i].r_fork = &forks[phs[i].num_of_philos - 1];
		else
			phs[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_data(t_data *data, t_philo *philos)
{
	data->dead_flag = 0;
	data->philos = philos;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
