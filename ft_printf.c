/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:01 by simarcha          #+#    #+#             */
/*   Updated: 2024/01/30 20:43:49 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(char c, va_list args, int ctr)
{
	ctr = 0;
	if (c == 'c')
		ctr = ft_putchar(va_arg(args, int));
	else if (c == 's')
		ctr = ft_putstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		ctr = ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		ctr = ft_putunsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		ctr = ft_puthexadecimal(va_arg(args, unsigned int));
	else if (c == 'X')
		ctr = ft_puthexadecimal_upper(va_arg(args, unsigned int));
	else if (c == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		ctr++;
	}
	else if (c == 'p')
		ctr = ft_putpointer(va_arg(args, unsigned long long));
	else
		return (-1);
	return (ctr);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		ctr;
	int		percent;
	int		var;

	va_start(args, str);
	i = -1;
	ctr = 0;
	percent = 0;
	while (str[++i] != '\0')
	{
		var = 0;
		if (str[i] != '%')
		{
			if (ft_putchar(str[i]) == -1)
				return (-1);
		}
		else
		{
			var = ft_format(str[++i], args, ctr);
			if (var == -1)
				return (-1);
			ctr += var;
			percent++;
		}
	}
	va_end(args);
	return (i + ctr - (percent * 2));
}