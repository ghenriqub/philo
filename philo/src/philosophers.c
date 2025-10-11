/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:00:52 by lgertrud          #+#    #+#             */
/*   Updated: 2025/10/11 21:49:01 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philosophers(t_philosopher *philos, t_rules *rules)
{
	pthread_t	*threads;
	pthread_t	monitoring;
	int			i;

	threads = malloc(sizeof(pthread_t) * rules->num_philos);
	if (!threads)
		return ;
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philosopher_routine,
				&philos[i]) != 0)
		{
			pthread_mutex_lock(&rules->death_lock);
			rules->someone_died = 1;
			pthread_mutex_unlock(&rules->death_lock);
			break ;
		}
		i++;
	}
	if (pthread_create(&monitoring, NULL, monitor_routine, philos) == 0)
		pthread_join(monitoring, NULL);
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	free(threads);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_rules			*rules;

	philo = (t_philosopher *)arg;
	rules = philo->rules;
	if (rules->num_philos == 1)
		return (ft_one_philo(philo, rules));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_someone_died(philo, rules))
			return (NULL);
		ft_take_forks(philo, rules);
		if (!advance_time(rules, rules->time_to_eat))
			return (unlock_and_return(rules, philo));
		log_action(philo, "is sleeping", rules);
		pthread_mutex_unlock(&rules->forks[philo->id % rules->num_philos]);
		pthread_mutex_unlock(&rules->forks[philo->id - 1]);
		if (!advance_time(rules, rules->time_to_sleep))
			return (NULL);
		log_action(philo, "is thinking", rules);
		if (rules->num_philos % 2 != 0)
			usleep(1000);
	}
}

void	ft_take_forks(t_philosopher *philo, t_rules *rules)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = (philo->id % rules->num_philos);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&rules->forks[right]);
		log_action(philo, "has taken a fork", rules);
		pthread_mutex_lock(&rules->forks[left]);
		log_action(philo, "has taken a fork", rules);
	}
	else
	{
		pthread_mutex_lock(&rules->forks[left]);
		log_action(philo, "has taken a fork", rules);
		pthread_mutex_lock(&rules->forks[right]);
		log_action(philo, "has taken a fork", rules);
	}
	pthread_mutex_lock(&philo->eat_lock);
	philo->count_eat++;
	philo->last_meal = timestamp_ms();
	pthread_mutex_unlock(&philo->eat_lock);
	log_action(philo, "is eating", rules);
}

void	*ft_one_philo(t_philosopher *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->forks[0]);
	log_action(philo, "has taken a fork", rules);
	advance_time(rules, rules->time_to_die);
	pthread_mutex_lock(&rules->death_lock);
	if (!rules->someone_died)
	{
		pthread_mutex_lock(&rules->print_lock);
		printf("%ld %d died\n",
			timestamp_ms() - rules->start, philo->id);
		pthread_mutex_unlock(&rules->print_lock);
		rules->someone_died = 1;
	}
	pthread_mutex_unlock(&rules->death_lock);
	pthread_mutex_unlock(&rules->forks[0]);
	return (NULL);
}

void	*unlock_and_return(t_rules *rules, t_philosopher *philo)
{
	pthread_mutex_unlock(&rules->forks[philo->id - 1]);
	pthread_mutex_unlock(&rules->forks[philo->id % rules->num_philos]);
	return (NULL);
}
