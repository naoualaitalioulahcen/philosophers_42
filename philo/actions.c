/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:24:52 by nait-ali          #+#    #+#             */
/*   Updated: 2023/07/26 19:24:52 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	messages(char *str, t_philosophre *philo, int flg)
{
	long long	time;

	pthread_mutex_lock(&philo->data->affichage);
	time = get_time() - philo->data->start_time;
	printf("%lld %d %s\n", time, philo->id, str);
	if (flg)
		pthread_mutex_unlock(&philo->data->affichage);
}

void	actions(t_philosophre *philo)
{
	pthread_mutex_lock(philo->fork1);
	messages("has taken a fork", philo, 1);
	pthread_mutex_lock(philo->fork2);
	messages("has taken a fork", philo, 1);
	pthread_mutex_lock(&philo->mutex_last_eat[philo->id - 1]);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->mutex_last_eat[philo->id - 1]);
	messages("is eating", philo, 1);
	ft_usleep(philo->data->time_to_eat);
	philo->nbr_eat++;
	pthread_mutex_lock(&philo->data->lock);
	if (philo->nbr_eat == philo->data->nbr_repas)
		philo->data->sala++;
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	messages("is sleeping", philo, 1);
	ft_usleep(philo->data->time_to_sleep);
	messages("is thinking", philo, 1);
}
