/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:01:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/09/28 20:25:15 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_thinking(t_philo *philo)
{
	ft_write_status(THINKING, philo);
}

static void	ft_eat(t_philo *philo)
{
	ft_mutex_handler(&philo->first_fork->fork, LOCK);
	ft_write_status(TAKE_FIRST_FORK, philo);
	ft_mutex_handler(&philo->second_fork->fork, LOCK);
	ft_write_status(TAKE_FIRST_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
			ft_gettime(MILISECOND));
	philo->meals_counter++;
	ft_write_status(EATING, philo);
	ft_sleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	ft_mutex_handler(&philo->first_fork->fork, UNLOCK);
	ft_mutex_handler(&philo->second_fork->fork, UNLOCK);
}

void	*ft_dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_wait_threads(philo->table);
	while (!ft_simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		ft_eat(philo);
		ft_write_status(SLEEPING, philo);
		ft_sleep(philo->table->time_to_sleep, philo->table);
	}
	return (NULL);
}

void	ft_dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		;
	else
	{
		while (table->philo_nbr > ++i)
			ft_thread_handler(&table->philos[i].thread_id, ft_dinner_simulation,
					&table->philos[i], CREATE);
	}
	table->start_simulation = ft_gettime(MILISECOND);
	set_bool(&table->table_mutex, &table->threads_ready, true);
	i = -1;
	while (table->philo_nbr > ++i)
		ft_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
}
