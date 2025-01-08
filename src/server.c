/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:21:49 by halnuma           #+#    #+#             */
/*   Updated: 2025/01/08 09:18:47 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

/*
	Exemple :
	c = 00000101;
	i = 3;
	donc on va checker le 4e bit en partant de la droite. 
	(Parce qu'a i = 0 on va check << 0 donc le dernier bit, i = 1 le 2e etc...)
	si signal == SIGUSR1
		-> On veut que ce bit devienne un 1;
		-> On va attribuer a c une comparaison bit par bit entre c et (1 << i)
		  (1 = 00000001,i etant le nombre de fois qu'on va decaler
		  le 1 a droite) donc ici 00001000
		-> | veut dire OU donc si un des deux bit est un 1 ca va nous donner 1;
		-> Pour le premier bit (tjr en partant de la droite) c[0] = 1 et
		   (1 << i)[0] = 0 donc c[0] sera egal a 1, ce qui régale puisqu'on veut
		   garder la meme valeur de c juste changer le 4e bit en un 1;
		-> Ainsi de suite jusqu'au 4e bit, les 1 restent des 1 et les 0 restent
		   des 0.
		-> 4e -> c[3] = 0, (1 << i)[3] = 1 donc c[3] devient 1 car 1 | 0 = 1.
		-> Si c[3] avait été un 1 il le serait resté car 1 | 1 = 1;
		-> Le reste bouge pas
	si signal == SIGUSR2
		-> On veut que ce bit reste un 0, donc on touche a rien, incrémente i
		   et passe au prochain.
	Quand i = 8 c'est qu'on a traité 8 bits, donc un char, on le print puis on
	reset notre char et notre compteur.
*/

void	signal_handler(int signal)
{
	static int		i = 0;
	static int		c = 0;
	// static int		pid = 0;

	// if (!pid)
	// 	pid = info->si_pid;
	if (signal == SIGUSR1)
		c = c | (1 << i);
	i++;
	if (i == 8)
	{
		// if (!c)
		// 	kill(pid, SIGUSR1);
		write(1, &c, 1);
		c = 0;
		i = 0;
	}
}

int	main(void)
{
	// struct sigaction	sa;

	// sa.sa_sigaction = &signal_handler;
	// // sa.sa_flags = 0;
	// // sigemptyset(&sa.sa_mask);
	// // sigaddset(&sa.sa_mask, SIGUSR1);
	// // sigaddset(&sa.sa_mask, SIGUSR2);
	ft_printf("PID: %d\n", getpid());
	ft_printf("Waiting for message...\n");
	while (1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		// sigaction(SIGUSR1, &sa, NULL);
		// sigaction(SIGUSR2, &sa, NULL);
		// pause();
	}
	return (0);
}
