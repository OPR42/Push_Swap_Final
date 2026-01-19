/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:03:37 by orobert           #+#    #+#             */
/*   Updated: 2025/12/22 14:03:39 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_uint	ps_abs(int signed_value)
{
	if (signed_value < 0)
		return (-signed_value);
	return (signed_value);
}

int	ps_intlen(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

long long	ps_atolli(const char *nptr)
{
	size_t				i;
	unsigned long long	n;
	int					sign;

	i = 0;
	n = 0;
	sign = 1;
	while (nptr[i] == ' ' || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i])
	{
		if ('0' > nptr[i] || nptr[i] > '9')
			break ;
		n = (10 * n) + nptr[i] - '0';
		i++;
	}
	return (n * sign);
}

int	ps_isint(const char *nptr)
{
	size_t			i;

	i = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i])
	{
		if ('0' > nptr[i] || nptr[i] > '9')
			return (0);
		i++;
	}
	if (ps_atolli(nptr) > INT_MAX || ps_atolli(nptr) < INT_MIN)
		return (0);
	return (1);
}
