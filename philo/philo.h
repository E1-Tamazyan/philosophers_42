/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:11:16 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/16 18:15:28 by etamazya         ###   ########.fr       */
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
    int             end; //-1 error 0 success | //time_to_die amount_eat dead_ocrd if sb is ko
    pthread_mutex_t *end_mutex;
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
short   is_fine(t_info *info);
int     death_occurred(t_info *info);

// *main*
unsigned long   my_curr_time(void);
void            *start_simulation(void *info);
short           print_msg(t_info *info, int index, char *s, unsigned long time);
short	        eating(t_philo *philo);
void            my_usleep(t_philo *philo, unsigned long time);

#endif