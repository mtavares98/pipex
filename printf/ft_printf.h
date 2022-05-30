/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:19:12 by mtavares          #+#    #+#             */
/*   Updated: 2022/03/27 19:54:17 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned long		t_lu;
typedef unsigned int		t_ui;
# define HEXUP 				"0123456789ABCDEF"
# define HEXLO 				"0123456789abcdef"
# define DEC				"0123456789"
# define STR				0
# define CHAR				1

int		ft_putstr(char *str, char c, int is_char);
int		ft_putnbr(int n, char *str, int numdig);
int		ft_putlunbr_base(t_lu n, char *str, int base, int numdig);
int		ft_printf(const char *str, ...);

#endif