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
	if (vars->n == 1)
	{
		pthread_mutex_lock(&vars->forks[0]);
		ph_printf(vars, philo->nb, "has taken a fork");
		ft_usleep(vars->ttd + 2);
		return ;
	}
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_lock(&vars->forks[philo->nb - 1]);
		ph_printf(vars, philo->nb, "has taken a fork");
		pthread_mutex_lock(&vars->forks[philo->nb % vars->n]);
		ph_printf(vars, philo->nb, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&vars->forks[philo->nb % vars->n]);
		ph_printf(vars, philo->nb, "has taken a fork");
		pthread_mutex_lock(&vars->forks[philo->nb - 1]);
		ph_printf(vars, philo->nb, "has taken a fork");
	}
}

static void	eat(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&philo->lastmeal_mx);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->lastmeal_mx);
	ph_printf(vars, philo->nb, "is eating");
	ft_usleep(vars->tte);
}

static void	p_sleep(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	ph_printf(vars, philo->nb, "is sleeping");
	ft_usleep(vars->tts);
}

static void	think(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	ph_printf(vars, philo->nb, "is thinking");
	ft_usleep(vars->ttt);
}

void	*p_routine(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	if (philo->nb % 2 != 0)
		ft_usleep(vars->ttt);
	while (1)
	{
		if (should_end(vars))
			break ;
		take_forks(philo);
		eat(philo);
		pthread_mutex_unlock(&vars->forks[philo->nb % vars->n]);
		if (vars->n > 1)
			pthread_mutex_unlock(&vars->forks[philo->nb - 1]);
		if ((vars->meal_count != -1) && all_meals_eaten(philo))
			break ;
		p_sleep(philo);
		think(philo);
	}
	return (NULL);
}
