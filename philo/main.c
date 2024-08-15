/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:31:52 by etamazya          #+#    #+#             */
/*   Updated: 2024/08/15 16:02:24 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//1 function

int main(int argc, char **argv)
{
    t_info  info;
    int     i;
        
    i = 0;
    if(!args_inspect(argc, argv))
        return (1 && printf("Invalid arguments\n"));
    if(!args_distribute(&info, argv))
        return (1);
    if(!init_philos(&info))
        return (1);
    printf("Success\n");
    return (0);
}
