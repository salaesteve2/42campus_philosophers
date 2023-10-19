/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:28:46 by sasalama          #+#    #+#             */
/*   Updated: 2022/11/14 09:46:03 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	tables;
	int		x;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments");
		return (0);
	}
	x = ft_init(&tables, argv);
	if (x == 1)
	{
		printf("Error initializing mutex");
		return (0);
	}
	if (x == 2)
	{
		printf("Error in one argument");
		return (0);
	}
	if (ft_start(&tables))
	{
		printf("Error creating the threads");
		return (0);
	}
	return (0);
}
