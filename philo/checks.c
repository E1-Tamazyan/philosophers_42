/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:01:29 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/15 20:38:58 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//4 functions

short   is_fine(t_philo philo->info)
{
    int flag;
    
    pthread_mutex_lock(&(philos->end_mutex));
	flag = philos->end;
	pthread_mutex_unlock(&(philos->end_mutex));
}

// int	finished(t_philosophers *philos)
// {
// 	int	finished;

// 	pthread_mutex_lock(&(philos->finish_mutex));
// 	finished = philos->finish;
// 	pthread_mutex_unlock(&(philos->finish_mutex));
// 	return (finished);
// }


short args_inspect(int argc, char **argv)
{
    size_t  i;
    size_t  j;

    if (argc == 1 || (argc == 2 &&  !(argv[1][0])))
        return (0);
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
        return (1);
    }
    return (0);
}

int dead_occurred(t_info *info)
{
    int i;

    i = 0;
    while (i < info->amount_philo)
    {
        pthread_mutex_lock(&info->philos[i].last_meal_mutex);
        if ((int)(my_curr_time() - info->philos[i].last_meal) >= info->die_duration)
        {
            pthread_mutex_lock(info->end_mutex);
            info->end = 1;
            pthread_mutex_unlock(info->end_mutex);
            pthread_mutex_lock(info->print_mutex);
            printf("%lu %d dead\n", my_curr_time(), info->philos[i].seat);
            pthread_mutex_unlock(info->print_mutex);
            pthread_mutex_unlock(&info->philos[i].last_meal_mutex);
            return (1);
        }
        pthread_mutex_unlock(&info->philos[i].last_meal_mutex);
        i++;
    }
    return (0);
}

void print_msg(t_info *info, char *s, unsigned long long time)
{
    pthread_mutex_lock(info->print_mutex);
    if (dead_occurred(info))
        printf ("%llu ms, %d %s\n", time, info->philos->seat, s);
    pthread_mutex_unlock(info->print_mutex);
}