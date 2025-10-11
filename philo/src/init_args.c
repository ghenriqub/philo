/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:58:06 by lgertrud          #+#    #+#             */
/*   Updated: 2025/10/11 21:47:44 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_rules_from_args(t_rules *rules, char **argv)
{
	rules->num_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->meals_limit = -1;
	if (argv[5])
		rules->meals_limit = ft_atoi(argv[5]);
	rules->someone_died = 0;
}

void	set_args(t_rules *rules, char **argv)
{
	int	i;

	init_rules_from_args(rules, argv);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->num_philos);
	if (!rules->forks)
		return ;
	i = 0;
	while (i < rules->num_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&rules->forks[i]);
			free(rules->forks);
			rules->forks = NULL;
			return ;
		}
		i++;
	}
	pthread_mutex_init(&rules->print_lock, NULL);
	pthread_mutex_init(&rules->death_lock, NULL);
}

t_philosopher	*ft_init_philos(t_rules *rules)
{
	t_philosopher	*philos;
	int				i;

	philos = malloc(sizeof(t_philosopher) * rules->num_philos);
	if (!philos)
		return (NULL);
	i = 0;
	rules->start = timestamp_ms();
	while (i < rules->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].rules = rules;
		philos[i].last_meal = rules->start;
		philos[i].count_eat = 0;
		if (pthread_mutex_init(&philos[i].eat_lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&philos[i].eat_lock);
			free(philos);
			return (NULL);
		}
		i++;
	}
	return (philos);
}
