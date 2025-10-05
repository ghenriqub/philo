/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:21:02 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/05 17:37:35 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = ft_gettime(MILISECOND)
		- get_long(&philo->philo_mutex, &philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > (time_to_die))
		return (true);
	return (false);
}

void	*ft_monitor(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!ft_all_threads_running(&table->table_mutex,
			&table->nbr_threads_running, table->philo_nbr))
		usleep(100);
	while (!ft_simulation_finished(table))
	{
		i = -1;
		while ((table->philo_nbr > ++i) && !ft_simulation_finished(table))
		{
			if (ft_philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				ft_write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
