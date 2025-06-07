/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:09:05 by gmunoz            #+#    #+#             */
/*   Updated: 2025/06/07 17:48:58 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_args(char **argv)
{
	if (ph_atoi(argv[1]) > PHILO_MAX || ph_atoi(argv[1]) <= 0)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ph_atoi(argv[2]) <= 0)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ph_atoi(argv[3]) <= 0)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ph_atoi(argv[4]) <= 0)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && ph_atoi(argv[5]) < 0)
	{
		write(2, "Invalid number of times each philosopher must eat\n", 51);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid number of arguments.\n", 29), 1);
	if (check_args(argv) == 1)
		return (1);
	init_data(&data, philos);
	init_forks(forks, ph_atoi(argv[1]));
	init_phs(philos, &data, forks, argv);
	thread_create(&data, forks);
	destroy_mutex(NULL, &data, forks);
	return (0);
}
