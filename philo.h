/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:39:13 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/15 17:39:14 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <ctype.h>

typedef struct s_vars{
	int				eat;
	int				sleep;
	int				think;
	int				meal_count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_vars;

typedef struct	s_philo{
	pthread_t		id;
	int				meals_nb;
	struct timeval	last_meal;
}	t_philo;

int	valid_values(int argc, char **argv);

#endif
