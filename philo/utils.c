/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:10:51 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/12 11:12:01 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long    my_curr_time(void)
{
    unsigned long  dur; //milliseconds
    struct timeval      time; //microseconds

    gettimeofday(&time, 0);
    dur = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (dur);
}

void    args_distribute(t_info *info, char **argv)
{
	info->amount_philo = ft_atoi(argv[1]);
	info->die_duration = ft_atoi(argv[2]);
	info->eat_duration = ft_atoi(argv[3]);
	info->sleep_duration = ft_atoi(argv[4]);
	info->amount_eat = -1;
	if (argv[5])
	{
		info->amount_eat = ft_atoi(argv[5]);
		if (!info->amount_eat)
			exit(1);
	}
	//why do we need this: "IDK":
	pthread_mutex_init(&info->sync_mutex, NULL);
	info->start_day = my_curr_time();
	return ;
}

void	init_philos(t_info *info)
{
	(void)info;
	int	i;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->amount_philo);
	if (!info->philos)
		exit (1);
	while (++i < info->amount_philo)
	{
		info->philos[i].seat = i;
		info->philos[i].info = info;	
		pthread_create(&info->philos[i].thread, NULL, start_day, &info->philos[i]);
	}
	// i = 0;
	// while (i < (info -> amount_philo))
	// {
	// 	pthread_mutex_init(&(info->philos[i].last_meal_m), NULL);
	// 	pthread_mutex_init(&(info->philos[i].meal_count_m), NULL);
	// 	i++;
	// }
	printf("Success\n");
}
