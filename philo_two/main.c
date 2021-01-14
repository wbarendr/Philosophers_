/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 11:50:19 by Wester        #+#    #+#                 */
/*   Updated: 2020/12/13 21:32:41 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		*thread_loop(void *data_v)
{
	t_life		*life;
	t_data		*data;

	data = (t_data *)data_v;
	life = malloc(sizeof(t_life));
	if (life == NULL)
		return (NULL);
	exchange_data(data, life);
	while (*life->all_alive != 0 && life->rounds != 0)
	{
		if (grab_forks(data, life) == 2)
		{
			write(1, "hi\n", 3);
			break ;
		}
		if (*life->all_alive == 0 || sleep_now(life, data) == 2)
			break ;
		if (life->rounds > 0)
			life->rounds--;
	}
	life->done = true;
	return (NULL);
}

void		*check_alive_loop(void *data_v)
{
	t_data		*data;
	int			i;
	int			*alive;

	i = 0;
	data = (t_data *)data_v;
	alive = data->life_structs[i]->all_alive;
	while (*alive != 0)
	{
		while (i < data->nr_of_philo && *alive != 0)
		{
			if (can_we_eat(data->life_structs[i], data, 2))
			{
				write_string(get_time_now(), "died", data->life_structs[i],
				data);
				*alive = 0;
				sem_post(data->forks);
				return (NULL);
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}

int			make_threads(t_data *data, int i)
{
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * (data->nr_of_philo + 1));
	if (thread == NULL)
		return (put_str_error("thread failed..."));
	while (check_how_many(data->nr_of_philo, &i))
	{
		data->nr = i;
		if (pthread_create(&thread[i], NULL, thread_loop, data))
			return (thread_create_fail(thread));
		dont_let_the_tiny_bedbugs_bite(200);
	}
	dont_let_the_tiny_bedbugs_bite(1000);
	if (pthread_create(&thread[i], NULL, check_alive_loop, data))
		return (thread_create_fail(thread));
	while (i > 0)
	{
		i--;
		if (pthread_join(thread[i], NULL))
			return (thread_join_fail(thread));
		pthread_detach(thread[i]);
	}
	data->alive = 0;
	free(thread);
	return (0);
}

int			main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
		return (put_str_error("! not right amount of arguments !"));
	if (check_input(argv, &data))
		return (put_str_error("! one or more arguments are incorrect !"));
	i = data.nr_of_philo;
	data.life_structs = malloc(sizeof(t_life *) * data.nr_of_philo);
	if (!data.life_structs)
		return (put_str_error("Malloc Failed..."));
	make_threads(&data, -1);
	while (i > 0)
	{
		i--;
		free(data.life_structs[i]);
	}
	free(data.life_structs);
	return (0);
}
