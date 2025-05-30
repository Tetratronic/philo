/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:04:19 by abenkaro          #+#    #+#             */
/*   Updated: 2025/04/06 20:04:49 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_elapsed_time(struct timeval start)
{
	struct timeval	now;
	long			seconds;
	long			microseconds;

	gettimeofday(&now, NULL);
	seconds = now.tv_sec - start.tv_sec;
	microseconds = now.tv_usec - start.tv_usec;
	return (seconds * 1000 + microseconds / 1000);
}

long int	actual_time(void)
{
	struct timeval		current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	long	start;
	long	now;

	start = actual_time();
	while (1)
	{
		now = actual_time();
		if ((now - start) >= ms)
			break ;
		if ((ms - (now - start)) > 1)
			usleep(100);
	}
}

void	ph_printf(t_vars *vars, int nb, char *state)
{
	pthread_mutex_lock(&vars->print_mx);
	pthread_mutex_lock(&vars->running_mx);
	if (!vars->running)
	{
		pthread_mutex_unlock(&vars->running_mx);
		pthread_mutex_unlock(&vars->print_mx);
		return ;
	}
	pthread_mutex_unlock(&vars->running_mx);
	printf("%ld %d %s\n",
		get_elapsed_time(vars->start_time), nb, state);
	pthread_mutex_unlock(&vars->print_mx);
}

int	should_end(t_vars *vars)
{
	pthread_mutex_lock(&vars->running_mx);
	if (!vars->running)
	{
		pthread_mutex_unlock(&vars->running_mx);
		return (1);
	}
	pthread_mutex_unlock(&vars->running_mx);
	return (0);
}
