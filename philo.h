/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:28:37 by sasalama          #+#    #+#             */
/*   Updated: 2022/11/06 20:28:38 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				position;
	int				left_fork;
	int				right_fork;
	int				eats;
	long long		last_eat;
	struct s_table	*table;
	pthread_t		thread;
}	t_philo;

typedef struct s_table
{
	int				num_philo;
	t_philo			philosophers[250];
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				all_ate;
	int				phi_dead;
	long long		first_timestamp;
	pthread_mutex_t	write;
	pthread_mutex_t	eat;
	pthread_mutex_t	forks[250];
}	t_table;

int			ft_atoi(const char *str);
int			ft_init(t_table *tables, char *argv[]);
int			ft_start(t_table *tables);
long long	ft_time(void);
void		ft_print(t_table *tables, int position, char *s);
void		ft_sleep(long long time, t_table *tables);
long long	ft_time_diff(long long x, long long y);
int			ft_count(t_table *tables, t_philo *philo);

#endif