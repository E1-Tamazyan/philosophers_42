/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:01:29 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/14 10:54:22 by etamazya         ###   ########.fr       */
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

int dead_occurred(t_info *info)
{
    int i;

    i = 0;
    while (i < info->amount_philo)
    {
        pthread_mutex_lock(&info->philos[i].last_meal_m);
        if ((int)(my_curr_time() - info->philos[i].last_meal) >= info->die_duration)
        {
            pthread_mutex_lock(info->dead_ocrd_mutex);
            info->dead_ocrd = 1;
            pthread_mutex_unlock(info->dead_ocrd_mutex);
            pthread_mutex_lock(info->print_mutex);
            printf("%lu %d dead\n", my_curr_time(), info->philos[i].seat);
            // print_msg(info, "is dead", get_time());
            pthread_mutex_unlock(info->print_mutex);
            pthread_mutex_unlock(&info->philos[i].last_meal_m);
            return (1);
        }
        pthread_mutex_unlock(&info->philos[i].last_meal_m);
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