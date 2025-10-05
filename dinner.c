/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:01:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/05 16:59:02 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thinking(t_philo *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_sim)
		ft_write_status(THINKING, philo);
	if ((philo->table->philo_nbr % 2) == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_sleep(t_think * 0.42, philo->table);
}

static void	ft_eat(t_philo *philo)
{
	ft_mutex_handler(&philo->first_fork->fork, LOCK);
	ft_write_status(TAKE_FIRST_FORK, philo);
	ft_mutex_handler(&philo->second_fork->fork, LOCK);
	ft_write_status(TAKE_SECOND_FORK, philo);
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

void	*ft_lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		ft_gettime(MILISECOND));
	ft_increase_long(&philo->table->table_mutex,
		&philo->table->nbr_threads_running);
	ft_write_status(TAKE_FIRST_FORK, philo);
	while (!ft_simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	*ft_dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		ft_gettime(MILISECOND));
	ft_increase_long(&philo->table->table_mutex,
		&philo->table->nbr_threads_running);
	ft_desynchronize(philo);
	while (!ft_simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		ft_eat(philo);
		ft_write_status(SLEEPING, philo);
		ft_sleep(philo->table->time_to_sleep, philo->table);
		ft_thinking(philo, false);
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
		ft_thread_handler(&table->philos[0].thread_id, ft_lone_philo,
			&table->philos[0], CREATE);
	else
	{
		while (table->philo_nbr > ++i)
			ft_thread_handler(&table->philos[i].thread_id, ft_dinner_simulation,
				&table->philos[i], CREATE);
	}
	ft_thread_handler(&table->monitor, ft_monitor, table, CREATE);
	table->start_simulation = ft_gettime(MILISECOND);
	set_bool(&table->table_mutex, &table->threads_ready, true);
	i = -1;
	while (table->philo_nbr > ++i)
		ft_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	ft_thread_handler(&table->monitor, NULL, NULL, JOIN);
}
