/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:21:31 by halnuma           #+#    #+#             */
/*   Updated: 2024/12/25 18:04:29 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

void	send_signal(char *s_pid, char *message)
{
	int	pid;
	int	i;

	pid = ft_atoi(s_pid);
	while (*message)
	{
		i = 7;
		while (i >= 0)
		{
			if (*message & (1 << i))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			i--;
		}
		message++;
	}
}

int	main(int ac, char **av)
{
	if (ac > 1)
		send_signal(av[1], av[2]);
	return (0);
}
