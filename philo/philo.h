/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:11:16 by etamazya          #+#    #+#             */
/*   Updated: 2024/07/31 19:30:42 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct      s_philo
{
    int             index;
    int             has_fork_1;
    int             has_fork_2;
    int             eat_duration;
    int             sleep_duration;
    int             *can_eat;
    long            last_ate;
    pthread_t       philo_die;
    pthread_t       philo_live;
    pthread_mutex_t fork_1;
    pthread_mutex_t fork_2;
}                   t_philo;

void    check_argv(int argc, char **argv);


#endif