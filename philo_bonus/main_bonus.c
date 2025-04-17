/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:41:47 by abenkaro          #+#    #+#             */
/*   Updated: 2025/04/16 16:42:05 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	philo_process(t_philo *philo, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			take_forks(philo);
			eat(philo);
			free_forks(philo);
			p_sleep(philo);
			think(philo);
		}
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		i;

	init_vars(&vars);
	init_philos(&vars);
	i = -1;
	while (++i < vars.n)
	{
		gettimeofday(&vars->philos[i].last_meal);
		philo_process(&vars->philos[i], i);
	}
	while (1)
		if (wait(NULL))
			break ;
	kill(-1, SIGTERM);
	return (0);
}
