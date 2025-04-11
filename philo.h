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
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_vars{
	int				n;
	int				ttd;
	int				tte;
	int				tts;
	int				meal_count;
	bool			running;
	t_philo			*philos;
	struct timeval	start_time;
	pthread_mutex_t	running_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_vars;

typedef struct s_philo{
	pthread_t		id;
	int				nb;
	int				meals_nb;
	struct timeval	last_meal;
	t_vars			*vars;
}	t_philo;

int		valid_values(int argc, char **argv);
void	init_vars(t_vars *vars, char **argv);
int		init_philos(t_vars *vars);
int		init_mutexes(t_vars *vars);
int		clean_resources(t_vars *vars, int ret_value);
void	*p_routine(void *arg);
void	*monitor(void *arg);
long	get_elapsed_time(struct timeval start);
void	mutex_print(t_vars *vars, int nb);
long	actual_time(void);
void	ft_usleep(long int time_in_ms);
void	ph_printf(t_vars *vars, int nb, char *state);

#endif
