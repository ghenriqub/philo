/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:45:29 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/05 17:16:15 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	if (status != DIED && get_bool(&philo->philo_mutex, &philo->full))
		return ;
	if (status != DIED && ft_simulation_finished(philo->table))
		return ;
	ft_mutex_handler(&philo->table->write_mutex, LOCK);
	elapsed = ft_gettime(MILISECOND) - philo->table->start_simulation;
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !ft_simulation_finished(philo->table))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !ft_simulation_finished(philo->table))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING && !ft_simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !ft_simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld %d died\n", elapsed, philo->id);
	ft_mutex_handler(&philo->table->write_mutex, UNLOCK);
}
