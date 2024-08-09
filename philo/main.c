/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:31:52 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/09 19:50:24 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_info  info;
    int     i;
        
    i = 0;
    args_inspect(argc, argv);
    args_distribute(&info, argv);
    init_philos(&info);
    return (0);
}
