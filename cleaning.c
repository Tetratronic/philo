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

	pthread_mutex_destroy(&vars->running_mx);
	pthread_mutex_destroy(&vars->print_mx);
	i = -1;
	while (++i < vars->n)
	{
		pthread_mutex_destroy(&vars->forks[i]);
		pthread_mutex_destroy(&vars->philos[i].lastmeal_mx);
		pthread_mutex_destroy(&vars->philos[i].nbmeal_mx);
	}
}

void	free_mem(t_vars *vars)
{
	if (vars->philos)
		free(vars->philos);
	if (vars->forks)
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
