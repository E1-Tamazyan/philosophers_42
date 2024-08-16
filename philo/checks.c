/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:01:29 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/16 18:19:40 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//3 functions
//error (1), ok(0)
short   args_inspect(int argc, char **argv)
{
    size_t  i;
    size_t  j;

    if (argc == 1 || (argc == 2 &&  !(argv[1][0])))
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
// *************** check locks ***************
int death_occurred(t_info *info)
{
    int i;

    i = 0;
    while (i < info->amount_philo)
    {
        pthread_mutex_lock(&info->philos[i].last_meal_mutex);
        if ((int)(my_curr_time() - info->philos[i].last_meal) >= info->die_duration)
        {
            pthread_mutex_lock(info->end_mutex);
            info->end = -1; //-1 error 0 success
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

//flag => (philos->end) will contain -1 0;
//return 1(error), 0(ok), -1();
short   is_fine(t_info *info)
{
    short   flag;

    flag = 0;
    if (!pthread_mutex_lock(info->end_mutex))
    {
        flag = info->end;
        if (!pthread_mutex_unlock(info->end_mutex))
            return (flag);
        else
            return (1);
    }
    return (flag);
}
