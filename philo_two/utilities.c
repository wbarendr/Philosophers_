/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 12:25:36 by Wester        #+#    #+#                 */
/*   Updated: 2020/12/08 19:01:59 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int					can_we_eat(t_life *life, t_data *data, int move)
{
	bool ret;

	if (sem_wait(data->bon_appetit) == -1)
		return (2);
	if (move == 1)
	{
		life->last_eat = get_time_now();
		if (sem_post(data->bon_appetit) == -1)
			return (2);
		return (1);
	}
	else
	{
		ret = check_death(life);
		if (sem_post(data->bon_appetit) == -1)
			return (2);
		return (ret);
	}
}

int					check_death(t_life *life)
{
	if (life->done == true)
		return (0);
	if (life->last_eat + life->t_die < get_time_now())
		return (1);
	return (0);
}

int					grab_forks(t_data *data, t_life *life)
{
	if (sem_wait(data->forks) == -1)
		return (2);
	if (write_string(get_time_now(), "has taken a fork", life, data))
		return (2);
	if (sem_wait(data->forks) == -1)
		return (2);
	if (write_string(get_time_now(), "has taken a fork", life, data))
		return (2);
	if (can_we_eat(life, data, 1) == 2)
		return (2);
	if (write_string(get_time_now(), "is eating", life, data))
		return (2);
	dont_let_the_bedbugs_bite(life->t_eat);
	if (sem_post(data->forks) == -1)
		return (2);
	if (sem_post(data->forks) == -1)
		return (2);
	return (0);
}

int					sleep_now(t_life *life, t_data *data)
{
	if (write_string(get_time_now(), "is sleeping", life, data))
		return (2);
	dont_let_the_bedbugs_bite(life->t_sleep);
	if (write_string(get_time_now(), "is thinking", life, data))
		return (2);
	return (0);
}
