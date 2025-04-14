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
				pthread_mutex_lock(&vars->print);
				if (vars->philos[i].meals_nb != 0)
					printf("%ld %d died\n",
						get_elapsed_time(vars->start_time), vars->philos[i].nb);
				pthread_mutex_unlock(&vars->print);
				pthread_mutex_lock(&vars->running_mutex);
				vars->running = false;
				pthread_mutex_unlock(&vars->running_mutex);
				break ;
			}
			usleep(100);
		}
	}
	return (NULL);
}
