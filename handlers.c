/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:20:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/09/28 20:34:59 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (LOCK == opcode || UNLOCK == opcode))
		ft_exit_error("The value specified by mutex is invalid!");
	else if ((status == EINVAL) && (opcode == INIT))
		ft_exit_error("The value specified by attr is invalid!");
	else if (status == EDEADLK)
		ft_exit_error("A deadlock would occur if the thread blocked \
				waiting for mutex");
	else if (status == EPERM)
		ft_exit_error("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		ft_exit_error("The process cannot allocate enough memory \
				to create another mutex");
	else if (status == EBUSY)
		ft_exit_error("Mutex is locked");
}

void	ft_thread_handler(pthread_t	*thread, void *(*foo)(void *),
		void*data, t_opcode opcode)
{
	if (opcode == CREATE)
		ft_handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		ft_handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		ft_handle_thread_error(pthread_detach(*thread), opcode);
	else
		ft_exit_error("Wrong opcode for thread handle.");
}

static void	ft_handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (LOCK == opcode || UNLOCK == opcode))
		ft_exit_error("The value specified by mutex is invalid!");
	else if ((status == EINVAL) && (opcode == INIT))
		ft_exit_error("The value specified by attr is invalid!");
	else if (status == EDEADLK)
		ft_exit_error("A deadlock would occur if the thread blocked \
				waiting for mutex");
	else if (status == EPERM)
		ft_exit_error("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		ft_exit_error("The process cannot allocate enough memory \
				to create another mutex");
	else if (status == EBUSY)
		ft_exit_error("Mutex is locked");
}

void	ft_mutex_handler(t_mtx	*mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		ft_handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		ft_handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		ft_handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		ft_handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		ft_exit_error("Wrong opcode for mutex handle.");
}
