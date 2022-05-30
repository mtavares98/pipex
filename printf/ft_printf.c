/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:18:33 by mtavares          #+#    #+#             */
/*   Updated: 2022/05/30 13:09:50 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

static int	ft_format(const char *str, int i, va_list *args)
{
	if (str[i] == 'c')
		return (ft_putstr(0, va_arg(*args, int), CHAR));
	if (str[i] == 's')
		return (ft_putstr(va_arg(*args, char *), 0, STR));
	if (str[i] == 'd' || str[i] == 'i')
		return (ft_putnbr(va_arg(*args, int), DEC, 0));
	if (str[i] == 'u')
		return (ft_putlunbr_base((t_lu)va_arg(*args, t_ui), DEC, 10, 0));
	if (str[i] == 'x')
		return (ft_putlunbr_base((t_lu)va_arg(*args, t_ui), HEXLO, 16, 0));
	if (str[i] == 'X')
		return (ft_putlunbr_base((t_lu)va_arg(*args, t_ui), HEXUP, 16, 0));
	if (str[i] == '%')
		return (ft_putstr(0, '%', CHAR));
	if (str[i] == 'p')
		return (write(1, "0x", 2) + ft_putlunbr_base(va_arg(*args, t_lu),
				HEXLO, 16, 0));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	size_t		i;
	size_t		counter;

	va_start(args, str);
	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '%')
			counter += ft_format(str, ++i, &args);
		else
			counter += ft_putstr(0, str[i], CHAR);
		i++;
	}
	va_end(args);
	return (counter);
}
