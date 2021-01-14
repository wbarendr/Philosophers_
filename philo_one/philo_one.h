/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 11:51:44 by Wester        #+#    #+#                 */
/*   Updated: 2020/12/07 18:19:58 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

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
}					t_life;

typedef struct		s_data
{
	int						nr_of_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nr_of_sleep;
	int						nr;
	int						alive;
	pthread_mutex_t			*forks;
	pthread_mutex_t			mutex_write;
	pthread_mutex_t			bon_appetit;
	t_life					**life_structs;
}					t_data;

int					put_str_error(char *str);
int					write_string(unsigned long time, char *text,
					t_life *life, t_data *data);
void				ft_putnbr(unsigned long num);

int					ft_atoi(char *str);
bool				check_input(char **argv, t_data *data);
void				exchange_data(t_data *data, t_life *life);
int					can_we_eat(t_life *life, t_data *data, int move);

unsigned long int	get_time_now(void);
int					check_death(t_life *life);
int					grab_forks(t_data *data, t_life *life);
int					sleep_now(t_life *life, t_data *data);
void				dont_let_the_bedbugs_bite(int sleepy_time);
void				dont_let_the_tiny_bedbugs_bite(int sleepy_time);

int					thread_create_fail(pthread_t *thread);
int					thread_join_fail(pthread_t *thread);
bool				check_how_many(int num_of_philo, int *i);

#endif
