/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 13:20:43 by Wester        #+#    #+#                 */
/*   Updated: 2020/12/13 21:33:31 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					ft_atoi(char *str)
{
	long int	num;
	int			i;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != 0)
		return (0);
	return (num);
}

bool				init_mutex(int amount, t_data *data)
{
	int i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * amount);
	if (data->forks == NULL)
		return (true);
	if (pthread_mutex_init(&data->mutex_write, NULL) ||
		pthread_mutex_init(&data->bon_appetit, NULL))
	{
		free(data->forks);
		return (true);
	}
	while (i < amount)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (false);
}

bool				check_input2(t_data *data)
{
	if (data->nr_of_philo <= 1 || data->nr_of_philo > 200)
	{
		put_str_error("amount of philosophers should be between 2 and 200");
		return (true);
	}
	if (data->time_to_die < 60 || data->time_to_eat < 60 ||
		data->time_to_sleep < 60)
	{
		put_str_error("time should not be under 60 miliseconds");
		return (true);
	}
	return (false);
}

bool				check_input(char **argv, t_data *data)
{
	int i;
	int num[5];

	num[4] = -1;
	i = 1;
	while (argv[i])
	{
		num[i - 1] = ft_atoi(argv[i]);
		if (num[i - 1] == 0)
			return (true);
		i++;
	}
	data->nr_of_philo = num[0];
	data->time_to_die = num[1];
	data->time_to_eat = num[2];
	data->time_to_sleep = num[3];
	data->nr_of_sleep = num[4];
	if (check_input2(data))
		return (true);
	if (init_mutex(num[0], data))
		return (true);
	data->alive = 1;
	return (false);
}

void				exchange_data(t_data *data, t_life *life)
{
	life->nr = data->nr;
	life->done = false;
	life->all_alive = &data->alive;
	life->t_die = data->time_to_die;
	life->t_eat = data->time_to_eat;
	life->t_sleep = data->time_to_sleep;
	life->rounds = data->nr_of_sleep;
	life->last_eat = get_time_now();
	data->life_structs[life->nr] = life;
	if (life->nr == data->nr_of_philo - 1)
		life->next = 0;
	else
		life->next = life->nr + 1;
}
