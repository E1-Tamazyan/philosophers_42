/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:01:29 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/22 20:31:20 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	args_inspect(int argc, char **argv)
{
	size_t	i;
	size_t	j;

	if (argc == 1 || (argc == 2 && !(argv[1][0])))
		return (1);
	if (argc == 5 || argc == 6)
	{
		i = 1;
		while (argv[i])
		{
			j = 0;
			while (argv[i][j])
			{
				if (argv[i][j] < '0' || argv[i][j] > '9')
					return (0);
				if (j > 11)
					return (0);
				j++;
			}
			i++;
		}
		return (0);
	}
	return (1);
}

int	death_occurred(t_info *info, int i)
{
	while (++i < info->amount_philo)
	{
		if (pthread_mutex_lock(&info->philos[i].last_meal_mutex))
			return (1);
		if ((int)(my_time() - info->philos[i].last_meal)
			>= info -> die_duration)
		{
			if (pthread_mutex_lock(&info->end_mutex))
				return (1);
			info->end = 1;
			if (pthread_mutex_unlock(&(info->end_mutex))
				|| pthread_mutex_lock(&(info->print_mutex)))
				return (1);
			printf("%lu %d %s\n", my_time(), info->philos[i].seat + 1, "died");
			if (pthread_mutex_unlock(&info->philos[i].last_meal_mutex)
				|| pthread_mutex_unlock(&(info->print_mutex)))
				return (1);
			return (1);
		}
		if (pthread_mutex_unlock(&info->philos[i].last_meal_mutex))
			return (1);
	}
	return (0);
}

int	is_fine(t_philo *philo)
{
	int	flag;

	flag = 0;
	if (pthread_mutex_lock(&(philo->info->end_mutex)))
		return (1);
	flag = *philo->is_dead;
	if (pthread_mutex_unlock(&philo->info->end_mutex) != 0)
		return (1);
	return (flag);
}

int	check_meal(t_info *info, int i)
{
	int	complete;

	complete = 0;
	if (info->amount_eat == -1)
		return (0);
	while (++i < info->amount_philo)
	{
		if (pthread_mutex_lock(&(info->philos[i].meal_counter_mutex)))
			return (1);
		if (info -> philos[i].meal_counter >= info -> amount_eat)
			complete++;
		if (pthread_mutex_unlock(&(info->philos[i].meal_counter_mutex)))
			return (1);
	}
	if (complete == info->amount_philo)
	{
		if (pthread_mutex_lock(&(info->end_mutex)))
			return (1);
		info->end = 1;
		if (pthread_mutex_unlock(&(info->end_mutex)))
			return (1);
		return (1);
	}
	return (0);
}

short	infinite_loop_destroy(t_info *info)
{
	int	i;

	while (1)
		if (death_occurred(info, -1) || check_meal(info, -1))
			break ;
	i = -1;
	while (++i < info -> amount_philo)
		if (pthread_join(info->philos[i].t, NULL))
			return (1);
	i = -1;
	while (++i < info -> amount_philo)
		if (pthread_mutex_destroy(&(info->forks[i]))
			|| pthread_mutex_destroy(&(info->philos[i].last_meal_mutex))
			|| pthread_mutex_destroy(&(info->philos[i].meal_counter_mutex)))
			return (1);
	if (pthread_mutex_destroy(&(info -> end_mutex))
		|| pthread_mutex_destroy(&(info -> print_mutex)))
		return (1);
	free(info->philos);
	free(info->forks);
	return (0);
}
