/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:23:15 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/24 02:41:56 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_values(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	while (*++argv)
	{
		i = -1;
		while ((*argv)[++i])
			if (!isdigit((*argv)[i]))
				return (0);
	}
	return (1);
}
