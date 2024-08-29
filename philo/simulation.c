/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:59:14 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/22 19:57:35 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork_r_mutex))
		return (1);
	print_msg(philo, philo->seat, "has taken a fork", my_time());
	if (philo->info->amount_philo == 1)
		return (1);
	if (pthread_mutex_lock(philo -> fork_l_mutex))
		return (1);
	print_msg(philo, philo->seat, "has taken a fork", my_time());
	print_msg(philo, philo->seat, "is eating", my_time());
	my_usleep(philo->info->eat_duration);
	if (pthread_mutex_unlock(philo->fork_r_mutex)
		|| pthread_mutex_unlock(philo->fork_l_mutex)
		|| pthread_mutex_lock(&(philo->meal_counter_mutex)))
		return (1);
	philo->meal_counter++;
	if (pthread_mutex_unlock(&(philo->meal_counter_mutex)))
		return (1);
	return (0);
}

void	*simul(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->fork_l_mutex = &philo->info->forks[philo->seat];
	philo->fork_r_mutex = &philo->info->forks[(philo->seat + 1)
		% philo->info->amount_philo];
	if ((philo -> seat + 1) % 2 == 0)
		usleep(1000);
	while (is_fine(philo) == 0)
	{
		if (eating(philo) == 1)
		{
			pthread_mutex_unlock(philo->fork_r_mutex);
			return (NULL);
		}
		if (pthread_mutex_lock(&(philo->last_meal_mutex)))
			return ((void *)1);
		philo->last_meal = my_time();
		if (pthread_mutex_unlock(&(philo->last_meal_mutex)))
			return ((void *)1);
		print_msg(philo, philo->seat, "is sleeping", my_time());
		my_usleep(philo->info->sleep_duration);
		print_msg(philo, philo->seat, "is thinking", my_time());
	}
	return (NULL);
}
