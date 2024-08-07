/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:01:29 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/07 18:51:59 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    args_inspect(int argc, char **argv)
{
    size_t  i;
    size_t  j;

    if (argc == 1 || (argc == 2 &&  !(argv[1][0])))
        exit(1);
    if (argc == 5 || argc == 6)
    {
        i = 1;
        while (argv[i])
        {
            j = 0;
            while (argv[i][j])
            {
                if (argv[i][j] < '0' || argv[i][j] > '9')
                    exit (1);
                if (j > 11)
                    exit (1);
                j++;
            }
            i++;
        }
        return ;
    }
    exit (printf("Invalid amount of arguments\n"));
}

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
	int	i;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->amount_philo);
	if (!info->philos)
		exit (1);
	while (++i < info->amount_philo)
	{
		info->philos[i].info = info;
		info->philos[i].seat = i;
		pthread_mutex_init(info->philos[i].fork_r, NULL);
		pthread_mutex_init(info->philos[i].fork_l, NULL);
		pthread_mutex_init(info->philos[i].last_meal_m, NULL);
		pthread_mutex_init(info->philos[i].meal_count_m, NULL);
		pthread_create(&info->philos[i].thread, NULL, start_day, &info->philos[i]);
		if (i == info->amount_philo)
			info->philos[i].fork_l = info->philos[0].fork_r;
		else
			info->philos[i].fork_l = info->philos[i + 1].fork_r;
		printf("Hello_%d\n", i);
	}
}
// don't forget to pthread_exit() function  at the end of the starting routine