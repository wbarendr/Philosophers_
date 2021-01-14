/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 12:25:36 by Wester        #+#    #+#                 */
/*   Updated: 2020/12/09 16:34:31 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int					can_we_eat(t_life *life, int move)
{
	bool ret;

	if (sem_wait(life->bon_appetit) == -1)
		return (2);
	if (move == 1)
	{
		life->last_eat = get_time_now();
		if (sem_post(life->bon_appetit) == -1)
			return (2);
		return (1);
	}
	else
	{
		ret = check_death(life);
		if (sem_post(life->bon_appetit) == -1)
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
	if (write_string(get_time_now(), "has taken a fork", life))
		return (2);
	if (sem_wait(data->forks) == -1)
		return (2);
	if (write_string(get_time_now(), "has taken a fork", life))
		return (2);
	if (can_we_eat(life, 1) == 2)
		return (2);
	if (write_string(get_time_now(), "is eating", life))
		return (2);
	dont_let_the_bedbugs_bite(life->t_eat);
	if (sem_post(data->forks))
		return (2);
	if (sem_post(data->forks))
		return (2);
	return (0);
}

int					sleep_now(t_life *life)
{
	if (write_string(get_time_now(), "is sleeping", life))
		return (2);
	dont_let_the_bedbugs_bite(life->t_sleep);
	if (write_string(get_time_now(), "is thinking", life))
		return (2);
	return (0);
}
