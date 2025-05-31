/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guido <guido@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:09:05 by gmunoz            #+#    #+#             */
/*   Updated: 2025/05/31 17:29:18 by guido            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ph_atoi(argv[1], 2);
	data->time_to_die = ph_atoi(argv[2], 3);
	data->time_to_eat = ph_atoi(argv[3], 4);
	data->time_to_sleep = ph_atoi(argv[4], 5);
	if (argc == 6)
		data->num_meals = ph_atoi(argv[5], 6);
	else
		data->num_meals = -1;
	if (data->num_philos == -1 || data->time_to_die == -1 ||
	    data->time_to_eat == -1 || data->time_to_sleep == -1 ||
	    (argc == 6 && data->num_meals == -1))
	{
		printf("Error: Invalid arguments.\n");
		return (-1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (-1);
	for (int i = 0; i < data->num_philos; i++)
		pthread_mutex_init(&data->forks[i], NULL);
	return (0);
}

void	*munch(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	// Simulate philosopher actions (eating, sleeping, thinking)
	printf("Philosopher %d is thinking.\n", philo->id);
	usleep(1000); // Simulate thinking time
	printf("Philosopher %d is eating.\n", philo->id);
	usleep(1000); // Simulate eating time
	printf("Philosopher %d is sleeping.\n", philo->id);
	usleep(1000); // Simulate sleeping time
	return NULL;
}

int	create_philosophers(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (-1);
	for (int i = 0; i < data->num_philos; i++)
	{
		data->philos[i].id = i + 1;
		data->philos[i].forks = data->forks;
		if (pthread_create(&data->philos[i].thread, NULL, munch, NULL) != 0)
		{
			free(data->philos);
			return (-1);
		}
		pthread_join(data->philos[i].thread, NULL);
	}
	return (0);
}

void	start_simulation(t_data *data)
{
	// Simulation logic would go here, such as starting threads and managing philosopher actions.
	// For now, we will just print a message.
	printf("Simulation started with %d philosophers.\n", data->num_philos);
}

void	cleanup(t_data *data)
{
	for (int i = 0; i < data->num_philos; i++)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	if (init_data(&data, argc, argv) == -1)
	{
		printf("Error: Initialization failed.\n");
		return (1);
	}
	if (create_philosophers(&data) == -1)
	{
		printf("Error: Failed to create philosophers.\n");
		return (1);
	}
	start_simulation(&data);
	cleanup(&data);
	return (0);
}
