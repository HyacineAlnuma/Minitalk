/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:21:31 by halnuma           #+#    #+#             */
/*   Updated: 2025/01/13 13:24:44 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk_bonus.h"

void	send_null_char(int pid)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		while (g_bit_received)
			pause();
		g_bit_received = 1;
		i++;
	}
}

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
	send_null_char(pid);
}

void	signal_handler(int signal)
{
	g_bit_received = 0;
	if (signal == SIGUSR2)
		ft_printf("\033[92mMessage has been received by the server!\n");
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
