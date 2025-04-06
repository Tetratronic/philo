/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:29:13 by abenkaro          #+#    #+#             */
/*   Updated: 2025/04/06 17:32:37 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_vars(t_vars *vars, char **argv)
{
	vars->n = atoi(argv[1]);
	vars->ttd = atoi(argv[2]);
	vars->tte = atoi(argv[3]);
	vars->tts = atoi(argv[4]);
	if (argv[5])
		vars->meal_count = atoi(argv[5]);
	else
		vars->meal_count = -1;
	gettimeofday(&vars->start_time);
}

int	init_philos(t_vars *vars)
{
	int	i;

	vars->philos = malloc(vars->n * sizeof(t_philo));
	if (!vars->philos)
		return (0);
	i = -1;
	while (++i < vars->n)
	{
		vars->philos.nb = i + 1;
		vars->philos.meals_nb = 0;
		vars->philos.dead = 0;
		vars->philos.vars = vars;
	}
	return (1);
}

int	init_mutexes(t_vars *vars)
{
	int	i;

	vars->forks = malloc(vars->n * sizeof(pthread_mutex_t));
	if (!vars->forks)
		return (0);
	i = -1;
	while (++i < vars->n)
		pthread_mutex_init(&vars->forks[i], NULL);
	pthread_mutex_init(&vars->print, NULL);
	pthread_mutex_init(&vars->running_mutex, NULL);
	return (1);
}
