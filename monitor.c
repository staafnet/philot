/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:26:33 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/21 13:06:56 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_philos(t_philo *philos, t_data *data)
{
	int		i;
	long	current_time;
	int		max_meals;

	while (!data->stop_simulation)
	{
		max_meals = 0;
		i = 0;
		while (i < data->number_of_philos)
		{
			if (philos[i].meals_eaten < data->meals_needed)
				max_meals = 1;
			i++;
		}
		i = 0;
		while (i < data->number_of_philos)
		{
			current_time = timestamp_in_ms();
			if (data->meals_needed > 0 && max_meals == 0)
			{
				data->stop_simulation = 1;
				return ;
			}
			if (current_time - philos[i].last_meal_time > data->time_to_die)
			{
				print_status(&philos[i], "died");
				data->stop_simulation = 1;
				return ;
			}

			i++;
		}
		usleep(1000);
	}
}
