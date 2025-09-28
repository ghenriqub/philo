/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:10:24 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/09/28 20:35:34 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		ft_parse_input(&table, argv);
		ft_data_init(&table);
		ft_dinner_start(&table);
		//ft_clean(&table);
	}
	else
	{
		ft_exit_error(RED"Wrong input: \n"RST
			"Correct is ./philo 5 800 200 200 [5]");
	}
}
