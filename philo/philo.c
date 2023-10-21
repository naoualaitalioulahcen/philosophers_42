/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:24:59 by nait-ali          #+#    #+#             */
/*   Updated: 2023/07/26 19:24:59 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos->mutex_last_eat[i]);
	}
	pthread_mutex_destroy(&data->affichage);
	pthread_mutex_destroy(&data->lock);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	if (data->philos->mutex_last_eat)
		free(data->philos->mutex_last_eat);
}

void	init_philos(t_data *data)
{
	pthread_mutex_t	*tmp;
	int				i;

	i = 0;
	tmp = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!tmp)
		return ;
	while (i < data->num_of_philo)
		pthread_mutex_init(&tmp[i++], NULL);
	i = 0;
	while (i < data->num_of_philo)
	{
		data->philos[i].mutex_last_eat = tmp;
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].nbr_eat = 0;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data			*data;
	int				i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (erreur("ERROR\n", NULL));
	if (parsing(av, ac) || init_data(data, av, ac))
		return (free(data), 1);
	init_philos(data);
	if (thread_init(data))
		return (1);
	ft_exit(data);
	return (free(data), 0);
}
