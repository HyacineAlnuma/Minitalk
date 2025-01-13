/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:21:31 by halnuma           #+#    #+#             */
/*   Updated: 2025/01/13 13:19:17 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk_bonus.h"

/*
	Cette  fonction va envoyer la string bit par bit.
	Pour chaque char on va vérifier c & (1 << j) sachant que 1 = 00000001
	et que j représente le nombre de fois qu'on va décaler le 1 a gauche.
	& compare les 2 valeurs bit par bit, il faut que les 2 bit soient 
	égal a 1 pour que le résulat soit égal a 1, sachant que tous les
	bits de 1 sont égal a 0 sauf le j eme a partant de la droite, tous les bits
	du résultats seront égal a 0 sauf potentiellement le j eme, celui que l'on
	veut tester donc. En faisant ca on "masque" tous les autres bits que le j eme
	afin de tester uniquement celui-ci. Si le j eme bit de c est 1, le j eme
	bit du résultat sera 1, donnant donc un resultat != 0. On envoie donc dans
	ce cas SIGUSR1, stipulant que le j eme bit est 1. Si je j eme bit est 0, le
	j eme bit du resultat sera donc aussi zero, donnant donc résultat = 0, on
	envoit donc SIGUSR2, stipulant que le j eme bit est 0.
*/

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
