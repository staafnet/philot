/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 09:53:34 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/21 10:46:28 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo nbr_of_philos to_die to_eat to_sleep [meals]\n");
		return (1);
	}
	data->number_of_philos = atoi(argv[1]);
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	if (argc == 6)
		data->meals_needed = atoi(argv[5]);
	else
		data->meals_needed = -1;
	data->stop_simulation = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	return (0);
}

int	init_philos(t_data *data, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->number_of_philos);
	i = 0;
	while (i < data->number_of_philos)
	{
		(*philos)[i].id = i;
		(*philos)[i].time_to_die = data->time_to_die;
		(*philos)[i].last_meal_time = timestamp_in_ms();
		(*philos)[i].left_fork = &data->forks[i];
		(*philos)[i].right_fork
			= &data->forks[(i + 1) % data->number_of_philos];
		(*philos)[i].data = data;
		(*philos)[i].meals_eaten = 0;
		i++;
	}
	return (0);
}
