/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:01:29 by etamazya          #+#    #+#             */
/*   Updated: 2024/07/31 19:51:41 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    args_inspect(int argc, char **argv)
{
    size_t  i;
    size_t  j;

    if (argc == 1 || (argc == 2 &&  !(argv[1][0])))
        exit(1);
    if (argc == 5 || argc == 6)
    {
        i = 1;
        while (argv[i])
        {
            j = 0;
            while (argv[i][j])
            {
                if (argv[i][j] < '0' || argv[i][j] > '9')
                    exit (1);
                if (j > 11)
                    exit (1);
                j++;
            }
            printf("argv[i] == %s\n", argv[i]);
            i++;
        }
        return ;
    }
    exit (write(1, "Invalid amount of arguments\n", 28));
}
