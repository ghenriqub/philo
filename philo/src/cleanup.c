/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:29:49 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/11 21:40:28 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_rules *rules, t_philosopher *philos, int philo_count)
{
	int	i;

	i = 0;
	while (i < rules->num_philos && rules->forks)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	if (rules->forks)
		free(rules->forks);
	pthread_mutex_destroy(&rules->print_lock);
	pthread_mutex_destroy(&rules->death_lock);
	if (philos)
	{
		i = 0;
		while (i < philo_count)
		{
			pthread_mutex_destroy(&philos[i].eat_lock);
			i++;
		}
	}
}

void	cleanup_all(t_rules *rules, t_philosopher *philos, pthread_t *threads)
{
	if (threads)
		free(threads);
	destroy_mutexes(rules, philos, rules->num_philos);
	if (philos)
		free(philos);
	if (rules)
		free(rules);
}
