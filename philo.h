/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:53:57 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/10/05 16:59:35 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// libs

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

// red text
#define RST "\033[0m"
#define RED "\033[1;31m"

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

// enums

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}	t_time;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

// structs

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}				t_philo;

// container aka table

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		end_simulation;
	bool		threads_ready;
	long		nbr_threads_running;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}				t_table;

// dinner.c

void	ft_dinner_start(t_table *table);
void	*ft_dinner_simulation(void *data);
void	ft_thinking(t_philo *philo, bool pre_sim);

// getter_setter.c
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	ft_simulation_finished(t_table *table);

// handlers.c
void	ft_mutex_handler(t_mtx	*mutex, t_opcode opcode);
void	ft_thread_handler(pthread_t	*thread, void *(*foo)(void *),
			void*data, t_opcode opcode);

// init.c
void	ft_data_init(t_table *table);

// monitoring.c
void	*ft_monitor(void *data);

// parsing.c
void	ft_parse_input(t_table *table, char **argv);

// synchro.c
void	ft_wait_threads(t_table *table);
bool	ft_all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	ft_increase_long(t_mtx *mutex, long *value);
void	ft_desynchronize(t_philo *philo);

// utils.c
long	ft_gettime(t_time time);
void	ft_sleep(long usec, t_table *table);
void	ft_exit_error(const char *error);
void	*ft_malloc(size_t bytes);
void	ft_clean(t_table *table);

// write.c
void	ft_write_status(t_philo_status status, t_philo *philo);
