/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:10:51 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/22 20:27:52 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//dur = miliseconds 
//time = microseconds
unsigned long	my_time(void)
{
	static long long	start;
	struct timeval		t1;

	if (start == 0)
	{
		gettimeofday(&t1, NULL);
		start = (t1.tv_sec * 1000 + t1.tv_usec / 1000);
	}
	gettimeofday(&t1, NULL);
	return ((t1.tv_sec * 1000) + (t1.tv_usec / 1000) - start);
}

short	args_distribute(t_info *info, char **argv)
{
	info->amount_philo = ft_atoi(argv[1]);
	info->die_duration = ft_atoi(argv[2]);
	info->eat_duration = ft_atoi(argv[3]);
	info->sleep_duration = ft_atoi(argv[4]);
	info->end = 0;
	if (pthread_mutex_init(&info->print_mutex, NULL)
		|| pthread_mutex_init(&(info->end_mutex), NULL))
		return (1);
	if (info->amount_philo <= 0 || info->die_duration < 0
		|| info->eat_duration < 0 || info->sleep_duration < 0)
		return (1);
	if (argv[5])
	{
		info->amount_eat = ft_atoi(argv[5]);
		if (!info->amount_eat)
			return (1);
		if (info->amount_eat < 0)
			return (1);
	}
	else
		info->amount_eat = -1;
	return (0);
}

short	init_philos(t_info *info, int i)
{
	info->philos = malloc(sizeof(t_philo) * info->amount_philo);
	if (!info->philos)
		return (1);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->amount_philo);
	if (!info->forks)
		return (free(info->philos), 0);
	while (++i < info->amount_philo)
	{
		info->philos[i].seat = i;
		info->philos[i].info = info;
		info->philos[i].is_dead = &info->end;
		info->philos[i].last_meal = my_time();
		info->philos[i].meal_counter = 0;
		if (pthread_mutex_init(&(info->philos[i].last_meal_mutex), NULL)
			|| pthread_mutex_init(&(info->philos[i].meal_counter_mutex), NULL)
			|| pthread_mutex_init(&(info->forks[i]), NULL))
			return (1);
	}
	i = 0;
	while ((i < info->amount_philo)
		&& !pthread_create(&info->philos[i].t, NULL, simul, &info->philos[i]))
		++i;
	return (0);
}

short	print_msg(t_philo *philo, int index, char *s, unsigned long time)
{
	if (pthread_mutex_lock(&philo->info->print_mutex))
		return (1);
	if (!is_fine(philo))
		printf("%lu %d %s\n", time, index + 1, s);
	if (pthread_mutex_unlock(&philo->info->print_mutex))
		return (1);
	return (0);
}

void	my_usleep(unsigned long t)
{
	unsigned long	time;

	time = my_time();
	while (my_time() - time <= t)
		usleep(500);
}
