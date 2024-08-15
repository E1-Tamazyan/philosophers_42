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

// short	eating(t_philo *philo, pthread_mutex_t *l_fork, pthread_mutex_t *r_fork)
// {
// 	pthread_mutex_lock(r_fork);
// 	print(philo->data, philo->index, "has taken a fork");
// 	if (philo->data->number_of_philos == 1)
// 	{
// 		pthread_mutex_unlock(r_fork);
// 		return (0);
// 	}
// 	pthread_mutex_lock(l_fork);
// 	print(philo->data, philo->index, "has taken a fork");
// 	print(philo->data, philo->index, "is eating");
// 	ft_usleep(philo->data->time_to_eat, philo->data);
// 	pthread_mutex_unlock(r_fork);
// 	pthread_mutex_unlock(l_fork);
// 	pthread_mutex_lock(&(philo->number_of_times_he_ate_mutex));
// 	philo->number_of_times_he_ate++;
// 	pthread_mutex_unlock(&(philo->number_of_times_he_ate_mutex));
// 	return (1);
// }
//time_to_die amount_eat dead_ocrd

void *start_simulation(void *arg)
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
	// if (!philos->)
	if (!is_fine(philo->info))
	{
		printf("Cool\n");
	}
	return (arg);
}
