/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:04:53 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/17 20:54:57 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_cycle(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ph_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	thread_create(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, data->philos) != 0)
		destroy_mutex("Thread creation error", data, forks);
	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_cycle,
				&data->philos[i]) != 0)
			destroy_mutex("Thread creation error", data, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_mutex("Thread join error", data, forks);
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy_mutex("Thread join error", data, forks);
		i++;
	}
	return (0);
}
