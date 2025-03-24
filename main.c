/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:54:48 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/24 02:54:53 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(int id) {
    printf("Philosopher %d is thinking...\n", id);
    usleep(100);
}

void p_sleep(int id) {
    printf("Philosopher %d is sleeping...\n", id);
    usleep(100);
}

void eat(int id) {
    printf("Philosopher %d is eating...\n", id);
    usleep(100);
}

int	main(int argc, char **argv)
{
	t_vars			vars;
	t_philo			*philos;
	int				running;
	pthread_t		monitor_death;
	pthread_t		monitor_meals;
	
	running = 1;
	if (!valid_values(argc, argv))
		return (-1);
	init_vars(&vars);
	philos = init_philos();
	if (!philos)
		return (-1);
	pthread_create(monitor_death, NULL, death_monitor, NULL);
	pthread_create(monitor_meals, NULL, meals_monitor, NULL);
	while (*philos)
		pthread_create((*philos)->id, NULL, philosopher, *philos++);
}
