/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:11:16 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/22 20:31:26 by etamazya         ###   ########.fr       */
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

struct	s_info;

typedef struct s_philo
{
	int				seat;
	unsigned long	last_meal;
	int				meal_counter;
	int				*is_dead;
	pthread_t		t;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meal_counter_mutex;
	pthread_mutex_t	*fork_r_mutex;
	pthread_mutex_t	*fork_l_mutex;
	struct s_info	*info;
}					t_philo;

typedef struct s_info
{
	unsigned long	start_day;
	int				amount_philo;
	int				die_duration;
	int				eat_duration;
	int				sleep_duration;
	int				end;
	int				amount_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
}					t_info;

// *parsing*
int				ft_atoi(char *str);
short			args_inspect(int argc, char **argv);
short			args_distribute(t_info *info, char **argv);

// *data_init*
short			init_philos(t_info *info, int i);

// *check*
int				is_fine(t_philo *philo);
int				death_occurred(t_info *info, int i);
short			infinite_loop_destroy(t_info *info);
int				check_meal(t_info *info, int i);

// *utils*
unsigned long	my_time(void);
void			*simul(void *info);
short			print_msg(t_philo *p, int i, char *s, unsigned long t);
short			eating(t_philo *philo);
void			my_usleep(unsigned long time);

#endif