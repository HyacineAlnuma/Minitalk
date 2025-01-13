/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:21:49 by halnuma           #+#    #+#             */
/*   Updated: 2025/01/13 13:24:55 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk_bonus.h"

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int		i = 0;
	static int		c = 0;

	(void)context;
	if (signal == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
			kill(info->si_pid, SIGUSR2);
		write(1, &c, 1);
		c = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	ft_printf("Waiting for message...\n");
	sa.sa_sigaction = &signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
