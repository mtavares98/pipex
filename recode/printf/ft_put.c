/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:47:26 by mtavares          #+#    #+#             */
/*   Updated: 2022/03/27 19:55:45 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str, char c, int is_char)
{
	int	len;

	len = 0;
	if (is_char)
		return (write(1, &c, 1));
	if (!str)
		str = "(null)";
	while (str[len])
		len++;
	return (write(1, str, len));
}

static int	ft_writenbr(int n, char *str, int numdig)
{
	if (n > 9 || n < -9)
		numdig += ft_writenbr(n / 10, str, numdig);
	write(1, &str[(n % 10) * ((n > 0) - (n < 0))], 1);
	return (++numdig);
}

int	ft_putnbr(int n, char *str, int numdig)
{
	if (n < 0)
		ft_putstr(0, '-', CHAR);
	return ((n < 0) + ft_writenbr(n, str, numdig));
}

int	ft_putlunbr_base(t_lu n, char *str, int base, int numdig)
{
	if (n > (t_lu) base - 1)
		numdig += ft_putlunbr_base(n / base, str, base, numdig);
	write(1, &str[n % base], 1);
	return (++numdig);
}
