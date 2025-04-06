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
}

int	init_philos(t_vars *vars)
{
	t_philo *result;
	size_t	i;

	result = malloc(vars->n * sizeof(t_philo));
	if (!result)
		return (0);
	i = -1;
	while (++i < vars->n)
	{
		result[i].nb = i + 1;
		result[i].meals_nb = 0;
		result[i].dead = 0;
		result[i].vars = vars;
	}
	vars->philos = result;
	return (1);
}
