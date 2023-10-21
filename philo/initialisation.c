/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:24:47 by nait-ali          #+#    #+#             */
/*   Updated: 2023/07/26 19:24:47 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocation(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (erreur("ERROR\n", data));
	data->philos = malloc(sizeof(t_philosophre) * data->num_of_philo);
	if (!data->philos)
		return (erreur("ERROR\n", data));
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philos[0].fork2 = &data->forks[data->num_of_philo - 1];
	data->philos[0].fork1 = &data->forks[0];
	i = 1;
	while (i < data->num_of_philo)
	{
		data->philos[i].fork2 = &data->forks[i - 1];
		data->philos[i].fork1 = &data->forks[i];
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv, int argc)
{
	if (argc == 6)
		data->nbr_repas = ft_atoi(argv[5]);
	else
		data->nbr_repas = 0;
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->num_of_philo > 200 || data->time_to_die <= 60
		|| data->time_to_eat <= 60 || data->time_to_sleep <= 60
		|| data->num_of_philo <= 0)
		return (erreur("Erreur dans les arguments", NULL));
	data->start_time = 0;
	data->sala = 0;
	if (pthread_mutex_init(&data->affichage, NULL))
		return (erreur("ERROR\n", NULL));
	if (pthread_mutex_init(&data->lock, NULL))
		return (erreur("ERROR\n", NULL));
	if (allocation(data) || init_forks(data))
		return (1);
	return (0);
}
