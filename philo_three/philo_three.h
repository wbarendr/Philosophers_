/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 11:51:44 by Wester        #+#    #+#                 */
/*   Updated: 2020/12/13 21:30:07 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <fcntl.h>
# include <signal.h>

typedef struct		s_life
{
	int						nr;
	int						next;
	int						*all_alive;
	int						t_die;
	int						t_eat;
	int						t_sleep;
	int						rounds;
	unsigned long int		last_eat;
	bool					done;
	sem_t					*sema_write;
	sem_t					*bon_appetit;
	sem_t					*alive;
	int						last;
}					t_life;

typedef struct		s_data
{
	int						nr_of_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nr_of_sleep;
	int						nr;
	int						check;
	int						*pid;
	pthread_t				*thread;
	sem_t					*alive;
	sem_t					*forks;
	sem_t					*sema_write;
	sem_t					*bon_appetit;
	t_life					**life_structs;
}					t_data;

int					put_str_error(char *str);
int					write_string(unsigned long time, char *text,
					t_life *life);
void				ft_putnbr(unsigned long num);

int					can_we_eat(t_life *life, int move);
int					ft_atoi(char *str);
bool				check_input(char **argv, t_data *data);
void				exchange_data(t_data *data, t_life *life);

unsigned long int	get_time_now(void);
int					check_death(t_life *life);
int					grab_forks(t_data *data, t_life *life);
int					sleep_now(t_life *life);

void				dont_let_the_tiny_bedbugs_bite(int sleepy_time);
void				dont_let_the_bedbugs_bite(int sleepy_time);

void				*check_alive_loop(void *life_v);
void				*check_all_alive(void *data_v);
void				exit_loop2(pthread_t *thread, t_life *life);
void				exit_loop(pthread_t *thread, t_life *life);
bool				check_loop(t_data *data, int *i);

#endif
