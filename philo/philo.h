/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:11:16 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/04 18:23:26 by etamazya         ###   ########.fr       */
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
    int             has_fork_l;
    int             has_fork_r;
    int             *can_eat;
    long            last_meal;
    // pthread_t       philo_die;
    pthread_t       thread;
    pthread_mutex_t fork_r;
    pthread_mutex_t *fork_l;
    struct s_info   *info;
}                   t_philo;

typedef struct      s_info
{
    int             start_day;
    int             amount_philo;
    int             die_duration;
    int             eat_duration;
    int             sleep_duration;
    int             amount_eat;
    int             death_accurred;
    t_philo         *philos;
    pthread_mutex_t sync_mutex;
}                   t_info;

int             ft_atoi(char *str);
void            args_inspect(int argc, char **argv);
unsigned long   my_curr_time(void);
void            args_distribute(t_info *info, char **argv);
void            init_philos(t_info *info);

#endif