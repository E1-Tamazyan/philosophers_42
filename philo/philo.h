/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:11:16 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/07 19:33:33 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>

struct          s_info;

typedef struct  s_philo
{
    int             seat;
    long            last_meal;
    int              meal_count;
    pthread_t       thread; //used in init  
    pthread_mutex_t *last_meal_m;
    pthread_mutex_t *meal_count_m;
    pthread_mutex_t *fork_r;
    pthread_mutex_t *fork_l; // keep this or the bottom one
    struct s_info   *info;
}                   t_philo;

typedef struct      s_info
{
    long long       start_day;
    int             amount_philo;
    int             die_duration;
    int             eat_duration;
    int             sleep_duration;
    int             dead;
    pthread_mutex_t *dead_mutex;
    int             amount_eat;
    pthread_mutex_t *forks;
    t_philo         *philos;
    pthread_mutex_t sync_mutex;
}                   t_info;

int             ft_atoi(char *str);
void            args_inspect(int argc, char **argv);
unsigned long   my_curr_time(void);
void            args_distribute(t_info *info, char **argv);
void            init_philos(t_info *info);
void            *start_day(void *info);

#endif