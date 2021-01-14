/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 15:32:14 by Wester        #+#    #+#                 */
/*   Updated: 2020/12/07 16:23:24 by wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			put_str_error(char *str)
{
	int i;

	i = 0;
	write(1, "\033[0;31m", 7);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	write(1, "\033[0m", 4);
	return (1);
}

int			write_string(unsigned long time, char *text, t_life *life,
			t_data *data)
{
	int i;

	if (pthread_mutex_lock(&data->mutex_write))
		return (2);
	if (*life->all_alive == 0)
	{
		if (pthread_mutex_unlock(&data->mutex_write))
			return (2);
		return (0);
	}
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(life->nr + 1);
	write(1, " ", 1);
	i = 0;
	while (text[i])
	{
		write(1, &text[i], 1);
		i++;
	}
	write(1, "\n", 1);
	if (pthread_mutex_unlock(&data->mutex_write))
		return (2);
	return (0);
}

void		ft_putnbr(unsigned long num)
{
	char print;

	if (num <= 9)
	{
		print = num + '0';
		write(1, &print, 1);
		return ;
	}
	ft_putnbr(num / 10);
	ft_putnbr(num % 10);
}
