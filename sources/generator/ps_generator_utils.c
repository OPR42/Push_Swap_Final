/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_generator_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:56:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/31 17:56:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_gen_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ps_gen_putnbr_fd(nb / 10, fd);
	c = (nb % 10) + '0';
	write(fd, &c, 1);
}

uint32_t	ps_gen_random_range(uint32_t *seed, uint32_t max)
{
	uint32_t	ret;
	uint32_t	limit;

	if (max == 0)
		return (0);
	limit = 4294967295 - (4294967295 % max);
	while (1)
	{
		ret = *seed;
		ret ^= ret << 13;
		ret ^= ret >> 17;
		ret ^= ret << 5;
		*seed = ret;
		if (ret < limit)
			return (ret % max);
	}
}

float	ps_gen_disorder(t_gendata *d)
{
	int				i;
	int				j;
	unsigned long	mistakes;
	unsigned long	total_pairs;

	mistakes = 0;
	total_pairs = 0;
	i = 0;
	while (i < d->quantity)
	{
		j = i + 1;
		while (j < d->quantity)
		{
			total_pairs++;
			if (d->n[i] > d->n[j])
				mistakes++;
			j++;
		}
		i++;
	}
	return ((float)mistakes / (float)total_pairs);
}
