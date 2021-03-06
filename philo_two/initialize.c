/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 13:20:43 by Wester        #+#    #+#                 */
/*   Updated: 2020/12/13 21:31:52 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

int					init_semaphores(int amount, t_data *data)
{
	int check;

	check = sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, 0600, amount);
	if (data->forks == SEM_FAILED)
		return (2);
	check = sem_unlink("sema_write");
	data->sema_write = sem_open("sema_write", O_CREAT, 0600, 1);
	if (data->sema_write == SEM_FAILED)
		return (2);
	check = sem_unlink("bon_appetit");
	data->bon_appetit = sem_open("bon_appetit", O_CREAT, 0600, 1);
	if (data->bon_appetit == SEM_FAILED)
		return (2);
	return (0);
}

bool				check_input2(t_data *data)
{
	if (data->nr_of_philo <= 1 || data->nr_of_philo > 200)
	{
		put_str_error("! amount of philosophers should be between 2 and 200 !");
		return (true);
	}
	if (data->time_to_die < 60 || data->time_to_eat < 60 ||
		data->time_to_sleep < 60)
	{
		put_str_error("! time should not be under 60 miliseconds !");
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
	if (init_semaphores(num[0], data))
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
