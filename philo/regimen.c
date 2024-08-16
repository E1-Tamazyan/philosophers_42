/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regimen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:59:14 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/15 20:40:12 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//2 functions

//return 0(ok) and anything else (error)
// *** can check msgs, too ***
short	eating(t_philo *philo) 
{
	if (!pthread_mutex_lock(philo->fork_r_mutex))
		print_msg(philo->info, philo->seat, "has taken a fork");
	else
		return (-1);
	if (philo->info->amount_philo == 1)
		return(pthread_mutex_unlock(philo->fork_r_mutex));
	if (!pthread_mutex_lock(philo->fork_l_mutex))
	{
		print_msg(philo->info, philo->seat, "has taken a fork");
		print_msg(philo->info, philo->seat, "is eating");
		// ft_usleep(philo->info->eat_duration, philo->info);
	}
	else
		return (1);
	if (!pthread_mutex_unlock(philo->fork_r_mutex) && !pthread_mutex_unlock(philo->fork_l_mutex))
	{
		if (!pthread_mutex_lock(&(philo->meal_counter_mutex)))
			philo->meal_counter_mutex++;
		return(pthread_mutex_unlock(&(philo->meal_counter_mutex)), 1);
	}
	else
		return (1);
	return (0);
}

//the cases the simulation will stop
//in my situation
//usleep returns 0: Success ,-1: Failure
void	*start_simulation(void *arg)
{
    t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->seat == 0)
		philo->fork_r_mutex = &(philo->info->forks[philo->info->amount_philo - 1]);
	else
		philo->fork_r_mutex = &(philo->info->forks[philo->seat - 1]);
	philo->fork_l_mutex = &(philo->info->forks[philo->seat]);
	if ((philo -> seat + 1) % 2 == 0)
		usleep(100);
	while (!is_fine(philo->info))
	{
		if (!eating(philo, left_fork, right_fork))
			return (0);
		printf("Cool\n");
	}
	return (arg);
}
