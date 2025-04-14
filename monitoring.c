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
	pthread_mutex_lock(&vars->counter);
	if (vars->philos[i].meals_nb != 0)
		ph_printf(vars, vars->philos[i].nb, "died");
	pthread_mutex_unlock(&vars->counter);
	pthread_mutex_lock(&vars->running_mutex);
	vars->running = false;
	pthread_mutex_unlock(&vars->running_mutex);
}

int	all_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->counter);
	if (--philo->meals_nb <= 0)
	{
		pthread_mutex_unlock(&philo->vars->counter);
		return (1);
	}
	pthread_mutex_unlock(&philo->vars->counter);
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
			pthread_mutex_lock(&vars->meal_mutex);
			elapsed = get_elapsed_time(vars->philos[i].last_meal);
			pthread_mutex_unlock(&vars->meal_mutex);
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
