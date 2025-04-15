/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:07:47 by abenkaro          #+#    #+#             */
/*   Updated: 2025/04/06 20:08:56 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_simulation(t_vars *vars, int i)
{
	pthread_mutex_lock(&vars->running_mutex);
	vars->running = false;
	pthread_mutex_unlock(&vars->running_mutex);
	pthread_mutex_lock(&vars->philos[i].nbmeal_mx);
	pthread_mutex_lock(&vars->print);
	if (vars->n == 1 || vars->philos[i].meals_nb != 0)
		printf("%ld %d died\n",
			get_elapsed_time(vars->start_time), vars->philos[i].nb);
	pthread_mutex_unlock(&vars->print);
	pthread_mutex_unlock(&vars->philos[i].nbmeal_mx);
}

int	all_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->nbmeal_mx);
	if (--philo->meals_nb <= 0)
	{
		pthread_mutex_unlock(&philo->nbmeal_mx);
		return (1);
	}
	pthread_mutex_unlock(&philo->nbmeal_mx);
	return (0);
}

void	*monitor(void *arg)
{
	t_vars	*vars;
	int		i;
	long	elapsed;

	vars = (t_vars *)arg;
	while (1)
	{
		if (should_end(vars))
			break ;
		i = -1;
		while (++i < vars->n)
		{
			pthread_mutex_lock(&vars->philos[i].lastmeal_mx);
			elapsed = get_elapsed_time(vars->philos[i].last_meal);
			pthread_mutex_unlock(&vars->philos[i].lastmeal_mx);
			if (elapsed > vars->ttd)
			{
				end_simulation(vars, i);
				break ;
			}
			usleep(100);
		}
	}
	return (NULL);
}
