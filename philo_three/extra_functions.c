/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: wester <wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 19:08:10 by wester        #+#    #+#                 */
/*   Updated: 2020/12/13 21:30:20 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		exit_loop(pthread_t *thread, t_life *life)
{
	free(thread);
	free(life);
	exit(2);
}

void		exit_loop2(pthread_t *thread, t_life *life)
{
	sem_post(life->alive);
	free(thread);
	free(life);
	exit(2);
}

void		*check_all_alive(void *data_v)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)data_v;
	sem_wait(data->alive);
	while (i < data->nr_of_philo)
	{
		kill(data->pid[i], SIGTERM);
		i++;
	}
	return (NULL);
}

void		*check_alive_loop(void *life_v)
{
	t_life		*life;

	life = (t_life *)life_v;
	while (life->done == false)
	{
		if (can_we_eat(life, 2))
		{
			life->last = 1;
			write_string(get_time_now(), "died", life);
			sem_post(life->alive);
			return (NULL);
		}
	}
	return (NULL);
}

bool		check_loop(t_data *data, int *i)
{
	(*i)++;
	if (*i < data->nr_of_philo)
	{
		data->nr = *i;
		return (true);
	}
	return (false);
}
