/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:22:58 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/09/28 20:25:02 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*ft_is_valid(const char *str)
{
	const char	*number;
	int			len;

	len = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		ft_exit_error("Put a positive digits!");
	if (!ft_is_digit(*str))
		ft_exit_error("Put a digit!");
	number = str;
	while (ft_is_digit(*str++))
		++len;
	if (len > 10)
		ft_exit_error("The value is too big!");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	nbr;

	nbr = 0;
	str = ft_is_valid(str);
	while (ft_is_digit(*str))
		nbr = (nbr * 10) + (*str++ - 48);
	if (nbr > INT_MAX)
		ft_exit_error("The value is too big!");
	return (nbr);
}

void	ft_parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		ft_exit_error("Use timestamps > 60ms");
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}
