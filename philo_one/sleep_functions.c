/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: wester <wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 17:18:15 by wester        #+#    #+#                 */
/*   Updated: 2020/12/03 13:15:23 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

unsigned long int	get_time_now(void)
{
	struct timeval		time;
	unsigned long int	now;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000;
	now += time.tv_usec / 1000;
	return (now);
}

unsigned long int	get_time_now_nano(void)
{
	struct timeval		time;
	unsigned long int	now;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000000;
	now += time.tv_usec;
	return (now);
}

void				dont_let_the_tiny_bedbugs_bite(int sleepy_time)
{
	unsigned long		time_now;

	time_now = get_time_now_nano();
	while (get_time_now_nano() < time_now + sleepy_time)
	{
		usleep(10);
	}
}

void				dont_let_the_bedbugs_bite(int sleepy_time)
{
	unsigned long		time_now;

	time_now = get_time_now();
	while (get_time_now() < time_now + sleepy_time)
	{
		usleep(100);
	}
}
