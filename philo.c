/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:28:42 by sasalama          #+#    #+#             */
/*   Updated: 2022/11/14 09:40:13 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philo(t_table *tables)
{
	int	x;

	x = tables->num_philo;
	while (x >= 0)
	{
		tables->philosophers[x].position = x;
		tables->philosophers[x].eats = 0;
		tables->philosophers[x].left_fork = x;
		tables->philosophers[x].right_fork = (x + 1) % tables->num_philo;
		tables->philosophers[x].last_eat = 0;
		tables->philosophers[x].table = tables;
		x--;
	}
	return (0);
}

int	ft_mutex(t_table *tables)
{
	int	x;

	x = tables->num_philo;
	while (x >= 0)
	{
		if (pthread_mutex_init(&(tables->forks[x]), NULL))
			return (1);
		x--;
	}
	if (pthread_mutex_init(&(tables->write), NULL))
		return (1);
	if (pthread_mutex_init(&(tables->eat), NULL))
		return (1);
	return (0);
}

int	ft_init(t_table *tables, char *argv[])
{
	tables->num_philo = ft_atoi(argv[1]);
	tables->time_die = ft_atoi(argv[2]);
	tables->time_eat = ft_atoi(argv[3]);
	tables->time_sleep = ft_atoi(argv[4]);
	tables->all_ate = 0;
	tables->phi_dead = 0;
	if (tables->num_philo < 1 || tables->time_die < 0 || tables->time_eat < 0
		|| tables->time_sleep < 0 || tables->num_philo > 250)
		return (1);
	tables->num_eat = -1;
	if (argv[5])
	{
		tables->num_eat = ft_atoi(argv[5]);
		if (tables->num_eat <= 0)
			return (1);
	}
	if (ft_mutex(tables) == 1)
		return (2);
	ft_init_philo(tables);
	return (0);
}
