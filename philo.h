/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 09:45:16 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/21 10:45:38 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int				number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_needed;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	long			start_time;
	int				stop_simulation;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			time_to_die;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
	int				meals_eaten;
}	t_philo;

int		init_data(t_data *data, int argc, char **argv);
int		init_philos(t_data *data, t_philo **philos);
void	*philo_routine(void *philo);
void	monitor_philos(t_philo *philos, t_data *data);
long	timestamp_in_ms(void);
void	print_status(t_philo *philo, char *status);
void	clean_up(t_data *data, t_philo *philos);

#endif