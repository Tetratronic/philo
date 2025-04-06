/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:39:45 by abenkaro          #+#    #+#             */
/*   Updated: 2025/04/06 18:44:25 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_vars *vars)
{
	int	i;

	pthread_mutex_destroy(&vars->running_mutex);
	pthread_mutex_destroy(&vars->print);
	i = -1;
	while (++i < vars->n)
		pthread_mutex_destroy(&vars->forks[i]);
}

void	free_mem(t_vars *vars)
{
	free(vars->philos);
	free(vars->forks);
	vars->philos = NULL;
	vars->forks = NULL;
}

int	clean_resources(t_vars *vars, int ret_value)
{
	destroy_mutexes(vars);
	free_mem(vars);
	return (ret_value);
}
