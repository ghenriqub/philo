/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:17:20 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/04 19:36:03 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait_threads(t_table *table)
{
	while(!get_bool(&table->table_mutex, &table->threads_ready))
		;
}

bool	ft_all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	ft_mutex_handler(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	ft_mutex_handler(mutex, UNLOCK);
	return (ret);
}

void	ft_increase_long(t_mtx *mutex, long *value)
{
	ft_mutex_handler(mutex, LOCK);
	(*value)++;
	ft_mutex_handler(mutex, UNLOCK);
}

void	ft_desynchronize(t_philo *philo)
{
	if ((philo->table->philo_nbr % 2) == 0)
	{
		if ((philo->id % 2) == 0)
			ft_sleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			ft_thinking(philo, true);
	}
}
