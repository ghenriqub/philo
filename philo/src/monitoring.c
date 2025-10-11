/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:50:13 by lgertrud          #+#    #+#             */
/*   Updated: 2025/10/11 21:36:06 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_philosopher	*philos;
	t_rules			*rules;
	int				i;
	long			now;

	philos = (t_philosopher *)arg;
	rules = philos[0].rules;
	while (!check_died(rules))
	{
		i = -1;
		while (++i < rules->num_philos)
		{
			now = timestamp_ms();
			pthread_mutex_lock(&philos[i].eat_lock);
			if (now - philos[i].last_meal > rules->time_to_die
				&& !(rules->meals_limit > 0
					&& philos[i].count_eat >= rules->meals_limit))
				return (someone_dead(philos, rules, i, now));
			pthread_mutex_unlock(&philos[i].eat_lock);
		}
		if (is_finished(philos, rules))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	*someone_dead(t_philosopher *philos, t_rules *rules, int i, long now)
{
	pthread_mutex_lock(&rules->death_lock);
	if (!rules->someone_died)
	{
		pthread_mutex_lock(&rules->print_lock);
		printf("%ld %d died\n", now - rules->start, philos[i].id);
		pthread_mutex_unlock(&rules->print_lock);
		rules->someone_died = 1;
	}
	pthread_mutex_unlock(&rules->death_lock);
	pthread_mutex_unlock(&philos[i].eat_lock);
	return (NULL);
}

int	is_finished(t_philosopher *philos, t_rules *rules)
{
	int	finished;
	int	i;

	i = 0;
	finished = 1;
	if (rules->meals_limit <= 0)
		return (0);
	while (i < rules->num_philos)
	{
		pthread_mutex_lock(&philos[i].eat_lock);
		if (philos[i].count_eat < rules->meals_limit)
			finished = 0;
		pthread_mutex_unlock(&philos[i].eat_lock);
		i++;
	}
	if (finished)
	{
		pthread_mutex_lock(&rules->death_lock);
		rules->someone_died = 1;
		pthread_mutex_unlock(&rules->death_lock);
	}
	return (finished);
}

int	check_died(t_rules *rules)
{
	pthread_mutex_lock(&rules->death_lock);
	if (rules->someone_died == 1)
	{
		pthread_mutex_unlock(&rules->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&rules->death_lock);
	return (0);
}
