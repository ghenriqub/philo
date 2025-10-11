/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:43:07 by lgertrud          #+#    #+#             */
/*   Updated: 2025/10/11 21:48:01 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules			*rules;
	t_philosopher	*philos;

	if (!validate_args(argc, argv))
		return (1);
	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (1);
	set_args(rules, argv);
	if (!rules->forks)
	{
		free(rules);
		printf(ERROR_MUTEX);
		return (1);
	}
	philos = ft_init_philos(rules);
	if (!philos)
	{
		destroy_mutexes(rules, NULL, 0);
		free(rules);
		printf(ERROR_MALLOC);
		return (1);
	}
	ft_philosophers(philos, rules);
	cleanup_all(rules, philos, NULL);
}

void	log_action(t_philosopher *philo, const char *action, t_rules *rules)
{
	pthread_mutex_lock(&rules->death_lock);
	if (!rules->someone_died)
	{
		pthread_mutex_lock(&philo->rules->print_lock);
		printf("%ld %d %s\n",
			timestamp_ms() - rules->start, philo->id, action);
		pthread_mutex_unlock(&philo->rules->print_lock);
	}
	pthread_mutex_unlock(&rules->death_lock);
}

long	timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

int	advance_time(t_rules *rules, int stop)
{
	long	begin;

	begin = timestamp_ms();
	while (1)
	{
		pthread_mutex_lock(&rules->death_lock);
		if (rules->someone_died)
		{
			pthread_mutex_unlock(&rules->death_lock);
			return (0);
		}
		pthread_mutex_unlock(&rules->death_lock);
		if ((timestamp_ms() - begin) >= stop)
			break ;
		usleep(500);
	}
	return (1);
}

int	check_someone_died(t_philosopher *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->death_lock);
	if (rules->someone_died)
	{
		pthread_mutex_unlock(&rules->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&rules->death_lock);
	pthread_mutex_lock(&philo->eat_lock);
	if (rules->meals_limit > 0 && philo->count_eat >= rules->meals_limit)
	{
		pthread_mutex_unlock(&philo->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_lock);
	return (0);
}
