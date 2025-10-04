/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:17:20 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/04 18:13:59 by ghenriqu         ###   ########.fr       */
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
