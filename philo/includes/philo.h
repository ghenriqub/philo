/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:44:24 by lgertrud          #+#    #+#             */
/*   Updated: 2025/10/11 20:28:37 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define ERROR_NUM_ARGS "Error: Wrong number of arguments\n"
# define ERROR_NO_ISDIGIT "Error: Arguments must be positive numbers\n"
# define ERROR_MALLOC "Error: Memory allocation failed\n"
# define ERROR_THREAD "Error: Thread creation failed\n"
# define ERROR_MUTEX "Error: Mutex initialization failed\n"

typedef struct s_rules
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				meals_limit;
	int				someone_died;
	long			start;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*forks;
}	t_rules;

typedef struct s_philosopher
{
	int				id;
	long long		last_meal;
	int				count_eat;
	pthread_mutex_t	eat_lock;
	t_rules			*rules;
}	t_philosopher;

// Init args
int				validate_args(int argc, char **argv);
int				check_caracters(char **arr);
void			set_args(t_rules *rules, char **argv);
t_philosopher	*ft_init_philos(t_rules *rules);
// support functions
int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *str);
long			timestamp_ms(void);

// Main Logic
void			ft_philosophers(t_philosopher *philo, t_rules *rules);
void			*philosopher_routine(void *arg);
void			ft_take_forks(t_philosopher *philo, t_rules *rules);
void			*ft_one_philo(t_philosopher *philo, t_rules *rules);
void			*unlock_and_return(t_rules *rules, t_philosopher *philo);

// Monitoring
void			*monitor_routine(void *arg);
void			*someone_dead(t_philosopher *philos, t_rules *rules,
					int i, long now);
int				is_finished(t_philosopher *philos, t_rules *rules);
int				check_died(t_rules *rules);

// Actions
void			log_action(t_philosopher *philo, const char *action,
					t_rules *rules);
int				advance_time(t_rules *rules, int stop);
int				check_someone_died(t_philosopher *philo, t_rules *rules);

// Cleanup
void			cleanup_all(t_rules *rules, t_philosopher *philos,
					pthread_t *threads);
void			destroy_mutexes(t_rules *rules, t_philosopher *philos,
					int philo_count);
#endif
