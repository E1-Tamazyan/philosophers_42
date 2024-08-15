/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:10:51 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/15 20:44:02 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//3 functions

unsigned long    my_curr_time(void)
{
    unsigned long  dur; //milliseconds
    struct timeval      time; //microseconds

    gettimeofday(&time, 0);
    dur = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (dur);
}

short	args_distribute(t_info *info, char **argv)
{
	info->amount_philo = ft_atoi(argv[1]);
	info->die_duration = ft_atoi(argv[2]);
	info->eat_duration = ft_atoi(argv[3]);
	info->sleep_duration = ft_atoi(argv[4]);
	info->amount_eat = 0;
	//SIGSEGV hereeeeee // ==4958==The signal is caused by a WRITE memory access.
						// ==4958==Hint: address points to the zero page.
	// pthread_mutex_init(info->dead_ocrd_mutex, NULL);
	// pthread_mutex_init(info->print_mutex, NULL);
	if (argv[5])
	{
		info->amount_eat = ft_atoi(argv[5]);
		if (!info->amount_eat)
			return (0);
	}
	return (1);
}

short	init_philos(t_info *info)
{
	int	i;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->amount_philo);
	if (!info->philos)
		return (0);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->amount_philo);
	if (!info->forks)
		return (free(info->philos), 0);
	while (++i < info->amount_philo)
	{
		info->philos[i].seat = i;
		info->philos[i].info = info;
		info->philos[i].last_meal = 0;
		info->philos[i].meal_counter = 0;
		pthread_mutex_init(&(info->philos[i].last_meal_mutex), NULL);
		pthread_mutex_init(&(info->philos[i].meal_counter_mutex), NULL);
		pthread_mutex_init(&(info->forks[i]), NULL);
	}
	i = -1;
	while (++i < info->amount_philo)
		pthread_create(&info->philos[i].thread, NULL, start_simulation, &info->philos[i]);
	return (1);
}
