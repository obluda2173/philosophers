/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:36:40 by erian             #+#    #+#             */
/*   Updated: 2024/09/26 10:55:39 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.c"

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if ((status == EINVAL) 
		&& (opcode == LOCK || opcode == UNLOCK || opcode == DESTROY))
		exit_error("The value specified by mutex is invalid.\n");
	else if (status == EINVAL && opcode == INIT)
		exit_error("The value specified by attr is invalid.\n");
	else if (status == EDEADLK)
		exit_error("A deadlock would occur if the thread blocked"
			" waiting for mutex.\n");
	else if (status == EPERM)
		exit_error("The current thread does not hold a lock on mutex.\n");
	else if (status == ENOMEM) 
		exit_error("The process cannot allocate enough memory to"
			" create another mutex.\n");
	else if (status == EBUSY)
		exit_error("Mutex is locked.\n");
}

void	safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_error_mutex(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_error_mutex(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_error_mutex(pthread_mutex_intit(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_error_mutex(pthread_mutex_destroy(mutex), opcode);
	else
		exit_error("Invalid opcode.\n");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		exit_error("No resources to create another thread.\n");
	else if (status == EPERM)
		exit_error("The caller has no appropriate permission.\n");
	else if (status == EINVAL && opcode == CREATE)
		exit_error("The value specified by attr is invalid.\n");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		exit_error("The value specified by thread is not joinable.\n");
	else if (status == ESRCH)
		exit_error("No thread could be found corresponding to that specified"
			 "by the given thread ID, thread.\n");
	else if (status == EDEADLK)
		exit_error("A deadlock was detected or a value of thread specifies"
			 "the calling thread.\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		 void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		exit_error("Wrong opcode for thread_handle:"
			" use <CREATE> <JOIN> <DETACH>");
}
