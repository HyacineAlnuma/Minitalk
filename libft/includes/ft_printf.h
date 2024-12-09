/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:58:51 by halnuma           #+#    #+#             */
/*   Updated: 2024/11/20 13:05:21 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(const char *input, ...);
int		ft_print_vars(va_list vars, char next);
void	ft_putnbr_base(size_t n, char *base);
int		ft_ptrlen(size_t n, char *base, int count);
int		ft_printhex(unsigned int n, int base_case);
int		ft_hexlen(unsigned int n, char *base, int count);
int		ft_printunbr(unsigned int n);
int		ft_unbrlen(unsigned int n, int count);
int		ft_printchar(char c);
int		ft_printstr(char *s);
int		ft_printnbr(int n);
int		ft_nbrlen(int n, int count);
int		ft_printptr(size_t n, char *base);

#endif