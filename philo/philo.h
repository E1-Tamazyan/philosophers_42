/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:11:16 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/03 18:57:08 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct      s_philo
{
    int             seat;
    int             has_fork_1;
    int             has_fork_2;
    int             *can_eat;
    long            last_ate;
    pthread_t       philo_die;
    pthread_mutex_t fork_1;
    pthread_mutex_t fork_2;
}                   t_philo;

typedef struct      s_info
{
    int             amount_philo;
    int             die_duration;
    int             eat_duration;
    int             sleep_duration;
    int             amount_eat;
}                   t_info;

int             ft_atoi(char *str);
void            args_inspect(int argc, char **argv);
unsigned long   my_current_time(void);
void            args_distribute(t_info  *info, char **argv);

#endif