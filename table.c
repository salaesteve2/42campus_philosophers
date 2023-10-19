/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:28:23 by sasalama          #+#    #+#             */
/*   Updated: 2022/11/14 09:42:12 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo)
{
	t_table	*tables;

	tables = philo->table;
	pthread_mutex_lock(&(tables->forks[philo->left_fork]));
	ft_print(tables, philo->position, "has taken a fork");
	if (tables->num_philo == 1)
		return (1);
	pthread_mutex_lock(&(tables->forks[philo->right_fork]));
	ft_print(tables, philo->position, "has taken a fork");
	pthread_mutex_lock(&(tables->eat));
	ft_print(tables, philo->position, "is eating");
	philo->last_eat = ft_time();
	pthread_mutex_unlock(&(tables->eat));
	ft_sleep(tables->time_eat, tables);
	(philo->eats)++;
	pthread_mutex_unlock(&(tables->forks[philo->left_fork]));
	pthread_mutex_unlock(&(tables->forks[philo->right_fork]));
	return (0);
}

void	*p_thread(void *void_philo)
{
	t_philo	*philo;
	t_table	*tables;
	int		x;

	philo = (t_philo *)void_philo;
	tables = philo->table;
	if (philo->position % 2)
		usleep(15000);
	while (!(tables->phi_dead))
	{
		x = ft_eat(philo);
		if (tables->all_ate || x != 0)
			break ;
		ft_print(tables, philo->position, "is sleeping");
		ft_sleep(tables->time_sleep, tables);
		ft_print(tables, philo->position, "is thinking");
	}
	return (0);
}

void	ft_dead(t_table *tables, t_philo *philo)
{
	int	x;

	while (!(tables->all_ate))
	{
		x = 0;
		while (x < tables->num_philo && !(tables->phi_dead))
		{
			pthread_mutex_lock(&(tables->eat));
			if (ft_time() - philo[x].last_eat > tables->time_die)
			{
				ft_print(tables, x, "died");
				tables->phi_dead = 1;
			}
			pthread_mutex_unlock(&(tables->eat));
			usleep(100);
			x++;
		}
		if (tables->phi_dead)
			break ;
		x = ft_count(tables, philo);
		if (x == tables->num_philo)
			tables->all_ate = 1;
	}
}

void	ft_finish(t_table *tables, t_philo *philo)
{
	int	x;

	x = 0;
	while (x < tables->num_philo)
	{
		pthread_join(philo[x].thread, NULL);
		x++;
	}
	x = 0;
	while (x < tables->num_philo)
	{
		pthread_mutex_destroy(&(tables->forks[x]));
		x++;
	}
	pthread_mutex_destroy(&(tables->write));
	pthread_mutex_destroy(&(tables->eat));
}

int	ft_start(t_table *tables)
{
	int		x;
	t_philo	*philo;

	x = 0;
	philo = tables->philosophers;
	tables->first_timestamp = ft_time();
	while (x < tables->num_philo)
	{
		if (pthread_create(&(philo[x].thread), NULL, p_thread, &(philo[x])))
			return (1);
		philo[x].last_eat = ft_time();
		x++;
	}
	ft_dead(tables, tables->philosophers);
	ft_finish(tables, philo);
	return (0);
}
