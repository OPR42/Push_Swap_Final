/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_generator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 12:03:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/31 12:03:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static uintptr_t	ps_seed_from_malloc(int argc, char **argv)
{
	uint8_t			*m;
	uintptr_t		a;

	m = (uint8_t *)malloc(1);
	a = (uintptr_t)m ^ (uintptr_t)(&m) ^ (uintptr_t)argv ^ (uintptr_t)(&argc);
	free(m);
	return (a);
}

static uint32_t	ps_seed_from_env(int argc, char **argv)
{
	unsigned char	*p;
	uint32_t		s;
	int				i;
	uintptr_t		a;

	s = 42;
	i = 0;
	while (i < argc)
	{
		p = (unsigned char *)argv[i++];
		while (*p)
		{
			s ^= (uint32_t)(*p++);
			s *= 1337u;
		}
	}
	a = ps_seed_from_malloc(argc, argv);
	s ^= (uint32_t)a;
	s ^= (uint32_t)(a >> 32);
	s ^= s << 13;
	s ^= s >> 17;
	s ^= s << 5;
	if (s == 0)
		s = 1;
	return (s);
}

static void	ps_gen_increase_disorder(t_gendata *d, int goal, int lots, int k)
{
	int			i;
	int			j;
	t_uint		tmp;

	i = 0;
	j = 0;
	while (ps_gen_disorder(d) < (float)goal / 100)
	{
		while (k++ < lots + 1)
		{
			d->ops++;
			i = (i + ps_gen_random_range(&d->seed, 42)) % d->quantity;
			j = (j + ps_gen_random_range(&d->seed, 1337)) % d->quantity;
			if ((i < j && d->n[i] < d->n[j]) || (i > j && d->n[i] > d->n[j]))
			{
				tmp = d->n[i];
				d->n[i] = d->n[j];
				d->n[j] = tmp;
			}
		}
		k = 0;
	}
}

static int	ps_gen_init_data(t_gendata *d, char *qty, char *disorder)
{
	int	i;

	d->quantity = ps_atolli(qty);
	d->wanted_disorder = ps_atolli(disorder);
	if (d->quantity < 1 || d->wanted_disorder < 0 || d->wanted_disorder > 100)
		return (-1);
	d->n = (t_uint *)malloc((d->quantity) * sizeof(t_uint));
	if (!d->n)
		return (-1);
	d->ops = 0;
	i = 0;
	while (i < d->quantity)
	{
		if (d->wanted_disorder == 100)
			d->n[i] = d->quantity - i - 1;
		else
			d->n[i] = i;
		i++;
	}
	if (d->wanted_disorder > 0 && d->wanted_disorder < 100)
		ps_gen_increase_disorder(d, d->wanted_disorder, d->quantity / 100, 0);
	d->disorder = ps_gen_disorder(d);
	return (0);
}

int	main(int argc, char **argv)
{
	t_gendata	data;
	int			i;

	data.seed = ps_seed_from_env(argc, argv);
	if (argc != 3 || ps_gen_init_data(&data, argv[1], argv[2]) == -1)
	{
		write(2, "\nUsage :\n", 9);
		write(2, "    ./ps_rnd_gen <quantity> <disorder 0-100>\n\n", 46);
		return (-1);
	}
	i = 0;
	while (i < data.quantity)
	{
		ps_gen_putnbr_fd(data.n[i++], 1);
		write(1, "\n", 1);
	}
	ps_gen_debrief(&data);
	free(data.n);
	return (0);
}
