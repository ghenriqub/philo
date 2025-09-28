/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:08:20 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/09/28 19:13:55 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	ft_mutex_handler(mutex, LOCK);
	*dest = value;
	ft_mutex_handler(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	ft_mutex_handler(mutex, LOCK);
	ret = *value;
	ft_mutex_handler(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	ft_mutex_handler(mutex, LOCK);
	*dest = value;
	ft_mutex_handler(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	ft_mutex_handler(mutex, LOCK);
	ret = *value;
	ft_mutex_handler(mutex, UNLOCK);
	return (ret);
}

bool	ft_simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
