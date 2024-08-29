/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:31:52 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/22 20:27:59 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sign);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		i;

	i = 0;
	if (args_inspect(argc, argv))
		return (1 && printf("Invalid arguments\n"));
	if (args_distribute(&info, argv))
		return (1 && printf("Cannot distribute\n"));
	if (init_philos(&info, -1))
		return (1);
	if (infinite_loop_destroy(&info))
		return (1);
	return (0);
}
