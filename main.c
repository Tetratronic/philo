/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:54:48 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/27 05:27:02 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sim_abort(t_vars *vars)
{
	pthread_mutex_lock(&vars->running_mutex);
	vars->running = !vars->running;
	pthread_mutex_unlock(&vars->running_mutex);
}

void	protected_thread(t_vars *vars, int i)
{
	i = i + 0;
	if (pthread_create(&vars->philos[i].id, NULL, p_routine, &vars->philos[i]))
		sim_abort(vars);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	pthread_t	mon_id;
	int			i;

	if (!valid_values(argc, argv) || !init_vars(&vars, argv, argc))
		return (-1);
	if (!init_philos(&vars) ||!init_mutexes(&vars))
		return (free_mem(&vars), -1);
	i = -1;
	while (++i < vars.n)
	{
		protected_thread(&vars, i);
		usleep((vars.philos[i].nb % 3) * 100);
	}
	if (pthread_create(&mon_id, NULL, monitor, &vars))
		sim_abort(&vars);
	else
		pthread_join(mon_id, NULL);
	while (--i >= 0)
		pthread_join(vars.philos[i].id, NULL);
	return (clean_resources(&vars, 0));
}
