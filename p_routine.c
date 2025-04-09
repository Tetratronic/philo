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
		pthread_mutex_lock(&vars->forks[philo->nb % vars->n]);
	}
	else 
	{
		pthread_mutex_lock(&vars->forks[philo->nb % vars->n]);
		pthread_mutex_lock(&vars->forks[philo->nb - 1]);
	}
}

static void	eat(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&vars->print);
	printf("%ld %d has taken a fork\n", get_elapsed_time(vars->start_time), philo->nb);
    printf("%ld %d has taken a fork\n", get_elapsed_time(vars->start_time), philo->nb);
    printf("%ld %d is eating\n", get_elapsed_time(vars->start_time), philo->nb);
	pthread_mutex_unlock(&vars->print);
	usleep(vars->tte * 1000);
}

static void	p_sleep(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&vars->print);
	printf("%ld %d is sleeping\n", get_elapsed_time(vars->start_time), philo->nb);
	pthread_mutex_unlock(&vars->print);
	usleep(vars->tts * 1000);
}

static void	think(t_philo *philo)
{
	t_vars	*vars;
	long	ttt;
	
	vars = philo->vars;
	ttt = (vars->ttd - vars->tte - vars->tts) / vars->n;
	pthread_mutex_lock(&vars->print);
	printf("%ld %d is thinking\n", get_elapsed_time(vars->start_time), philo->nb);
	pthread_mutex_unlock(&vars->print);
	usleep(ttt * 1000);
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
			break;
		}
		pthread_mutex_unlock(&vars->running_mutex);
		take_forks(philo);
		gettimeofday(&philo->last_meal, NULL);
		philo->meals_nb++;
		eat(philo);
		pthread_mutex_unlock(&vars->forks[philo->nb % vars->n]);
		pthread_mutex_unlock(&vars->forks[philo->nb - 1]);
		p_sleep(philo);
		if (vars->meal_count != -1 && philo->meals_nb >= vars->meal_count)
			break ;
		think(philo);
	}
	return (NULL);
}
