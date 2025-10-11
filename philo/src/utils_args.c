/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:58:06 by lgertrud          #+#    #+#             */
/*   Updated: 2025/10/11 21:15:38 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	is_valid_number(char *str)
{
	int		i;
	long	num;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-' || !ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (0);
		i++;
	}
	num = ft_atoi(str);
	if (num <= 0 || num > INT_MAX)
		return (0);
	return (1);
}

int	validate_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf(ERROR_NUM_ARGS);
		return (0);
	}
	if (!check_caracters(argv))
	{
		printf(ERROR_NO_ISDIGIT);
		return (0);
	}
	return (1);
}

int	check_caracters(char **arr)
{
	int	i;

	i = 1;
	while (arr[i])
	{
		if (!is_valid_number(arr[i]))
			return (0);
		i++;
	}
	return (1);
}
