/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: wester <wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 14:04:53 by wester        #+#    #+#                 */
/*   Updated: 2020/12/13 21:32:26 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		thread_create_fail(pthread_t *thread)
{
	free(thread);
	return (put_str_error("creating thread failed"));
}

int		thread_join_fail(pthread_t *thread)
{
	free(thread);
	return (put_str_error("joining thread failed"));
}

bool	check_how_many(int num_of_philo, int *i)
{
	if (*i == -1)
		(*i)++;
	else
		*i += 2;
	if (*i >= num_of_philo && *i != 0 && *i % 2 == 0)
		*i = 1;
	if (*i < num_of_philo)
		return (true);
	*i = num_of_philo;
	return (false);
}
