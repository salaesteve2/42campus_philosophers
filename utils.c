/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:28:19 by sasalama          #+#    #+#             */
/*   Updated: 2022/11/14 09:43:39 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_print(t_table *tables, int position, char *s)
{
	pthread_mutex_lock(&(tables->write));
	if (!(tables->phi_dead))
	{
		printf("%lli ", ft_time() - tables->first_timestamp);
		printf("%i ", position + 1);
		printf("%s\n", s);
	}
	pthread_mutex_unlock(&(tables->write));
	return ;
}

void	ft_sleep(long long time, t_table *tables)
{
	long long	x;

	x = ft_time();
	while (!(tables->phi_dead))
	{
		if (ft_time() - x >= time)
			break ;
		usleep(50);
	}
}

int	ft_count(t_table *tables, t_philo *philo)
{
	int	x;

	x = 0;
	while (tables->num_eat != -1 && x < tables->num_philo
		&& philo[x].eats >= tables->num_eat)
		x++;
	return (x);
}
