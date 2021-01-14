/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 13:20:43 by Wester        #+#    #+#                 */
/*   Updated: 2020/12/03 13:17:56 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

void				init_semaphores(int amount, t_data *data)
{
	int check;

	check = sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, 0600, amount);
	check = sem_unlink("sema_write");
	data->sema_write = sem_open("sema_write", O_CREAT, 0600, 1);
	check = sem_unlink("bon_appetit");
	data->bon_appetit = sem_open("bon_appetit", O_CREAT, 0600, 1);
	check = sem_unlink("alive");
	data->alive = sem_open("alive", O_CREAT, 0600, 0);
	data->thread = malloc(sizeof(pthread_t));
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
	init_semaphores(num[0], data);
	return (false);
}

void				exchange_data(t_data *data, t_life *life)
{
	life->nr = data->nr;
	life->done = false;
	life->t_die = data->time_to_die;
	life->t_eat = data->time_to_eat;
	life->t_sleep = data->time_to_sleep;
	life->rounds = data->nr_of_sleep;
	life->last_eat = get_time_now();
	if (life->nr == data->nr_of_philo - 1)
		life->next = 0;
	else
		life->next = life->nr + 1;
	life->last = 0;
}
