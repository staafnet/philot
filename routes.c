/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:23:23 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/21 13:06:13 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;
	t_data	*data;
	int		i;
	int		max_meals;

	philo = (t_philo *)philo_ptr;
	data = philo->data;
	while (!data->stop_simulation)
	{
		print_status(philo, "thinking");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		print_status(philo, "eating");
		usleep(data->time_to_eat * 1000);
		philo->last_meal_time = timestamp_in_ms();
		philo->meals_eaten++;
		i = 0;
		max_meals = 0;
		while (i < data->number_of_philos)
		{
			if (philo->meals_eaten < data->meals_needed)
				max_meals = 1;
			i++;
		}

		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (data->meals_needed > 0 && max_meals == 0)
			return (NULL);
		print_status(philo, "sleeping");
		usleep(data->time_to_sleep * 1000);
	}
	return (NULL);
}
