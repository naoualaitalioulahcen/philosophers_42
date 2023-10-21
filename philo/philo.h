/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:28:53 by nait-ali          #+#    #+#             */
/*   Updated: 2023/07/26 20:28:53 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_data	t_data;

typedef struct s_philosophre
{
	t_data			*data;
	pthread_t		tid;
	int				id;
	int				nbr_eat;
	long long		last_eat;
	pthread_mutex_t	*mutex_last_eat;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}	t_philosophre;

typedef struct s_data
{
	int				num_of_philo;
	int				nbr_repas;
	int				sala;
	t_philosophre	*philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	affichage;
}	t_data;

int		ft_atoi(const char *str);
int		erreur(char *str, t_data *data);
void	messages(char *str, t_philosophre *philo, int flg);
void	ft_exit(t_data *data);
time_t	get_time(void);
int		ft_usleep(useconds_t time);
int		init(t_data *data, char **argv, int argc);
int		thread_init(t_data *data);
int		init_data(t_data *data, char **argv, int argc);
void	init_philos(t_data *data);
int		init_forks(t_data *data);
int		allocation(t_data *data);
int		parsing(char **argv, int ac);
void	actions(t_philosophre *philo);
void	*routine(void *philo_pointer);
#endif
