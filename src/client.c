/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:21:31 by halnuma           #+#    #+#             */
/*   Updated: 2025/01/13 13:24:50 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

void	send_signal(char *s_pid, char *message)
{
	int		pid;
	int		i;
	int		j;
	char	c;

	pid = ft_atoi(s_pid);
	i = 0;
	while (message[i])
	{
		j = 0;
		c = message[i];
		while (j < 8)
		{
			if (c & (1 << j))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			while (g_bit_received)
				pause();
			g_bit_received = 1;
			j++;
		}
		i++;
	}
}

void	signal_handler(int signal)
{
	(void)signal;
	g_bit_received = 0;
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (ac == 3)
		send_signal(av[1], av[2]);
	else if (ac > 3)
	{
		ft_printf("Error: Too many arguments\n");
		return (1);
	}
	else
	{
		ft_printf("Error: Not enough arguments\n");
		return (1);
	}
	return (0);
}
