/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:31:52 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/07 19:27:58 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_info  info;
    int     i;
    // void    *smth;
    
    i = 0;
    args_inspect(argc, argv);
    args_distribute(&info, argv);
    init_philos(&info);
    // smth = start_day(&info);
    start_day(&info);
        // start_day((struct s_info *) (void *) &info);
    return (0);
}
