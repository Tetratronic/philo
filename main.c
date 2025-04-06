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
#include <stdbool.h>

// void think(int id) {
//     printf("Philosopher %d is thinking...\n", id);
//     usleep(100);
// }
//
// void p_sleep(int id) {
//     printf("Philosopher %d is sleeping...\n", id);
//     usleep(100);
// }
//
// void eat(int id) {
//     printf("Philosopher %d is eating...\n", id);
//     usleep(100);
// }
//
// void	*thread_routine(void)
// {
// 	printf("Hey\n");
//
// 	return (NULL);
// }
//
// void	*monitor(void)
// {
//
// }

int	main(int argc, char **argv)
{
	t_vars		vars;
	pthread_t	monitor;
	int			i;

	if (!valid_values(argc, argv))
		return (-1);
	init_vars(&vars);
	if (!init_mutexes(&vars))
		return (clean_resources(&vars, -1));
	if (!init_philos(&vars))
		return (clean_resources(&vars, -1));
	i = -1;
	while (++i < vars->n)
	{
		pthread_create(vars.philos[i].id, NULL, p_routine, &vars.philos[i]);
		pthread_detach(vars.philos[i].id);
	}
	pthread_create(monitor, NULL, monitor, &vars);
	pthread_join(monitor);
	return (clean_resources(&vars, 0));
}
