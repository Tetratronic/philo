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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	result;
	int					sign;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (ft_isdigit(str[i]))
	{
		if ((result > (long)INT_MAX / 10)
			|| (result == INT_MAX / 10 && (str[i] - 48) > INT_MAX % 10 + 1))
			return ((long)INT_MAX + 1);
		result = (result * 10) + (str[i] - 48);
		if (result == (long)2147483648 && sign > 0)
			return ((long)INT_MAX + 1);
		i++;
	}
	return ((long)result * sign);
}

int	valid_values(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	while (*++argv)
	{
		i = -1;
		while ((*argv)[++i])
			if (!ft_isdigit((*argv)[i]))
				return (0);
	}
	return (1);
}
