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

int	main(int argc, char **argv)
{
	t_vars		vars;
	pthread_t	mon_id;
	int			i;

	if (!valid_values(argc, argv))
		return (-1);
	init_vars(&vars, argv);
	if (!init_mutexes(&vars) || !init_philos(&vars))
		return (clean_resources(&vars, -1));
	i = -1;
	while (++i < vars.n)
	{
		pthread_create(&vars.philos[i].id, NULL, p_routine, &vars.philos[i]);
		pthread_detach(vars.philos[i].id);
	}
	pthread_create(&mon_id, NULL, monitor, &vars);
	pthread_join(mon_id, NULL);
	return (clean_resources(&vars, 0));
}
