/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:11:16 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/15 20:37:29 by etamazya         ###   ########.fr       */
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
    unsigned long   last_meal;
    int             meal_counter;
    pthread_t       thread;
    pthread_mutex_t last_meal_mutex;
    pthread_mutex_t meal_counter_mutex;
    pthread_mutex_t *fork_r_mutex;
    pthread_mutex_t *fork_l_mutex;
    struct s_info   *info;
}                   t_philo;

typedef struct      s_info
{
    long long       start_day;
    int             amount_philo;
    int             die_duration;
    int             eat_duration;
    int             sleep_duration;
    int             end;
    pthread_mutex_t *end_flag;
    int             amount_eat;
    pthread_mutex_t *forks;
    t_philo         *philos;
    pthread_mutex_t *print_mutex;
    pthread_mutex_t sync_mutex; //dunno where to use
}                   t_info;

// *parsing*
int     ft_atoi(char *str);
short   args_inspect(int argc, char **argv);
short   args_distribute(t_info *info, char **argv);

// *data_init*
short   init_philos(t_info *info);

// *check*
short   is_fine(t_philo philo->info);
int     dead_occurred(t_info *info)

// *main*
unsigned long   my_curr_time(void);
void            *start_simulation(void *info);
void            print_msg(t_info *info, char *s, unsigned long long time);
// short	        eating(t_philo *philo, pthread_mutex_t *l_fork, pthread_mutex_t *r_fork);

#endif