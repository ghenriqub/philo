/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:52:26 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/04 17:26:04 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(position + 1) % philo_nbr];
	philo->second_fork = &forks[position];
	if ((philo->id % 2) == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
}

static void	ft_philo_init(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (table->philo_nbr > ++i)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		ft_mutex_handler(&philo->philo_mutex, INIT);
		ft_assign_forks(philo, table->forks, i);
	}
}

void	ft_data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->threads_ready = false;
	table->nbr_threads_running = 0;
	table->philos = ft_malloc(sizeof(t_philo) * table->philo_nbr);
	ft_mutex_handler(&table->table_mutex, INIT);
	ft_mutex_handler(&table->write_mutex, INIT);
	table->forks = ft_malloc(sizeof(t_fork) * table->philo_nbr);
	while (table->philo_nbr > ++i)
	{
		ft_mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	ft_philo_init(table);
}
