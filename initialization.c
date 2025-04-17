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

int	init_vars(t_vars *vars, char **argv, int argc)
{
	int		i;
	long	val;

	i = 1;
	while (i < argc)
	{
		val = ft_atoi(argv[i++]);
		if (val == (long)INT_MAX + 1 || val <= 0)
			return (0);
	}
	vars->n = (int)ft_atoi(argv[1]);
	vars->ttd = (int)ft_atoi(argv[2]);
	vars->tte = (int)ft_atoi(argv[3]);
	vars->tts = (int)ft_atoi(argv[4]);
	vars->ttt = (vars->ttd - vars->tte - vars->tts) / 2.29;
	vars->running = true;
	if (argv[5])
		vars->meal_count = (int)ft_atoi(argv[5]);
	else
		vars->meal_count = -1;
	gettimeofday(&vars->start_time, NULL);
	vars->philos = NULL;
	vars->forks = NULL;
	return (1);
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
		vars->philos[i].nb = i + 1;
		vars->philos[i].meals_nb = vars->meal_count;
		vars->philos[i].vars = vars;
		pthread_mutex_init(&vars->philos[i].nbmeal_mx, NULL);
		pthread_mutex_init(&vars->philos[i].lastmeal_mx, NULL);
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
	pthread_mutex_init(&vars->print_mx, NULL);
	pthread_mutex_init(&vars->running_mx, NULL);
	return (1);
}
