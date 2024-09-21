/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 09:48:48 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/21 09:52:37 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;
	int		i;

	if (init_data(&data, argc, argv) != 0 || init_philos(&data, &philos) != 0)
		return (1);
	i = 0;
	while (i < data.number_of_philos)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	monitor_philos(philos, &data);
	i = 0;
	while (i < data.number_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	clean_up(&data, philos);
	return (0);
}
