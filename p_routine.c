/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:02:04 by abenkaro          #+#    #+#             */
/*   Updated: 2025/04/06 19:03:10 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo	*philo)
{
	t_vars	*vars;

	vars = philo->vars;
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_lock(&vars->forks[philo->nb - 1]);
		mutex_print(vars, philo->nb);
		pthread_mutex_lock(&vars->forks[philo->nb % vars->n]);
		mutex_print(vars, philo->nb);
	}
	else
	{
		pthread_mutex_lock(&vars->forks[philo->nb % vars->n]);
		mutex_print(vars, philo->nb);
		pthread_mutex_lock(&vars->forks[philo->nb - 1]);
		mutex_print(vars, philo->nb);
	}
}

static void	eat(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&vars->print);
	printf("%ld %d is eating\n",
		get_elapsed_time(vars->start_time), philo->nb);
	pthread_mutex_unlock(&vars->print);
	ft_usleep(vars->tte);
}

static void	p_sleep(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&vars->print);
	printf("%ld %d is sleeping\n",
		get_elapsed_time(vars->start_time), philo->nb);
	pthread_mutex_unlock(&vars->print);
	ft_usleep(vars->tts);
}

static void	think(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&vars->print);
	printf("%ld %d is thinking\n",
		get_elapsed_time(vars->start_time), philo->nb);
	pthread_mutex_unlock(&vars->print);
}

void	*p_routine(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	while (1)
	{
		pthread_mutex_lock(&vars->running_mutex);
		if (!vars->running)
		{
			pthread_mutex_unlock(&vars->running_mutex);
			break ;
		}
		pthread_mutex_unlock(&vars->running_mutex);
		take_forks(philo);
		pthread_mutex_lock(&vars->meal_mutex);
		gettimeofday(&philo->last_meal, NULL);
		pthread_mutex_unlock(&vars->meal_mutex);
		eat(philo);
		philo->meals_nb++;
		pthread_mutex_unlock(&vars->forks[philo->nb % vars->n]);
		pthread_mutex_unlock(&vars->forks[philo->nb - 1]);
		if (vars->meal_count != -1 && philo->meals_nb >= vars->meal_count)
			break ;
		p_sleep(philo);
		think(philo);
	}
	return (NULL);
}
