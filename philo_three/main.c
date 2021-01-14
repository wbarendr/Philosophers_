/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 11:50:19 by Wester        #+#    #+#                 */
/*   Updated: 2020/12/13 21:29:49 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		proces_loop2(pthread_t *thread, t_life *life, t_data *data)
{
	while (life->rounds != 0)
	{
		if (grab_forks(data, life) == 2)
			exit_loop2(thread, life);
		if (sleep_now(life) == 2)
			exit_loop2(thread, life);
		if (life->rounds > 0)
			life->rounds--;
	}
	life->done = true;
	pthread_join(thread[0], NULL);
	free(thread);
	free(life);
	exit(2);
}

void		proces_loop(t_data *data)
{
	t_life		*life;
	pthread_t	*thread;

	life = malloc(sizeof(t_life));
	if (life == NULL)
		exit(2);
	thread = malloc(sizeof(pthread_t));
	if (thread == NULL)
	{
		free(life);
		exit(2);
	}
	exchange_data(data, life);
	life->sema_write = sem_open("sema_write", 0);
	life->bon_appetit = sem_open("bon_appetit", 0);
	life->alive = sem_open("alive", 0);
	if (life->sema_write == SEM_FAILED || life->bon_appetit == SEM_FAILED
		|| life->alive == SEM_FAILED)
		exit_loop(thread, life);
	if (pthread_create(&thread[0], NULL, check_alive_loop, life))
		exit_loop(thread, life);
	proces_loop2(thread, life, data);
}

int			make_proces(t_data *data, int i)
{
	int			pid[data->nr_of_philo + 1];

	while (check_loop(data, &i))
	{
		pid[i] = fork();
		if (pid[i] == 0)
			proces_loop(data);
		dont_let_the_tiny_bedbugs_bite(4000);
	}
	data->pid = pid;
	dont_let_the_tiny_bedbugs_bite(1000);
	if (pthread_create(&data->thread[0], NULL, check_all_alive, data))
		return (put_str_error("creating thread failed"));
	while (i > 0)
	{
		i--;
		if (waitpid(pid[i], NULL, 0) == -1)
			return (put_str_error("waitpid failed"));
	}
	if (sem_post(data->alive) == -1)
		return (put_str_error("sem post failed"));
	if (pthread_join(data->thread[0], NULL))
		return (put_str_error("thread join failed"));
	return (0);
}

int			main(int argc, char **argv)
{
	t_data		data;
	int			ret;

	if (argc != 5 && argc != 6)
		return (put_str_error("! not right amount of arguments !"));
	if (check_input(argv, &data))
		return (put_str_error("! one or more arguments are incorrect !"));
	ret = make_proces(&data, -1);
	free(data.thread);
	return (ret);
}
