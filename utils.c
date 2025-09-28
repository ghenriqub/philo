/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:12:12 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/09/28 19:44:37 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		ft_exit_error("Malloc error...");
	return (ret);
}

void	ft_exit_error(const char *error)
{
	printf(RED "%s\n" RST, error);
	exit(EXIT_FAILURE);
}

long	ft_gettime(t_time time)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		ft_exit_error("gettimeofday failed!");
	if (time == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time == MILISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		ft_exit_error("Wrong input to gettime!");
	return (1337);
}

void	ft_sleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = ft_gettime(MICROSECOND);
	while (ft_gettime(MICROSECOND) - start < usec)
	{
		if (ft_simulation_finished(table))
			break ;
		elapsed = ft_gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(usec / 2);
		else
		{
			while (ft_gettime(MICROSECOND) - start < usec)
				;
		}
	}
}
