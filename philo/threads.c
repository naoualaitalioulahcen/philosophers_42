/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:35:22 by nait-ali          #+#    #+#             */
/*   Updated: 2023/07/26 20:35:22 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_pointer)
{
	t_philosophre	*philo;

	philo = (t_philosophre *) philo_pointer;
	pthread_mutex_lock(&philo->mutex_last_eat[philo->id - 1]);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->mutex_last_eat[philo->id - 1]);
	if (!(philo->id % 2))
		usleep(600);
	while (1)
		actions(philo);
	return ((void *)0);
}

int	check_max_eat(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	if (data->sala == data->num_of_philo && data->nbr_repas)
	{
		pthread_mutex_unlock(&data->lock);
		pthread_mutex_lock(&data->affichage);
		return (0);
	}
	pthread_mutex_unlock(&data->lock);
	return (1);
}

int	ft_death(t_data *data)
{
	int			i;
	long long	time;

	while (1)
	{
		i = -1;
		usleep(500);
		if (!check_max_eat(data))
			return (0);
		while (++i < data->num_of_philo)
		{
			pthread_mutex_lock(&data->philos[i] \
			.mutex_last_eat[data->philos[i].id - 1]);
			time = get_time() - data->philos[i].last_eat;
			pthread_mutex_unlock(&data->philos[i]. \
			mutex_last_eat[data->philos[i].id - 1]);
			if (time >= data->time_to_die)
			{
				messages("died", &data->philos[i], 0);
				return (0);
			}
		}
	}
	return (1);
}

int	thread_init(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->num_of_philo)
	{
		if (pthread_create(&data->philos[i]. \
		tid, NULL, &routine, &data->philos[i]))
			return (erreur("ERROR\n", data));
		pthread_detach(data->philos[i].tid);
	}
	if (!ft_death(data))
		return (0);
	return (0);
}
