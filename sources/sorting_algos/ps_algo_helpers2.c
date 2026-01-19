/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_helpers1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 02:10:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/19 02:10:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	stacks_doublerotate(t_data *data, int *rot_a, int *rot_b)
{
	if (*rot_a > 0 && *rot_b > 0)
	{
		ps_exec(data, "rr", 1);
		(*rot_a)--;
		(*rot_b)--;
	}
	else if (*rot_a < 0 && *rot_b < 0)
	{
		ps_exec(data, "rrr", 1);
		(*rot_a)++;
		(*rot_b)++;
	}
}

void	ps_stacks_rotate(t_data *data, int rot_a, int rot_b)
{
	while (rot_a != 0 || rot_b != 0)
	{
		if ((rot_a > 0 && rot_b > 0) || (rot_a < 0 && rot_b < 0))
			stacks_doublerotate(data, &rot_a, &rot_b);
		else if (rot_a > 0)
		{
			ps_exec(data, "ra", 1);
			rot_a--;
		}
		else if (rot_a < 0)
		{
			ps_exec(data, "rra", 1);
			rot_a++;
		}
		else if (rot_b > 0)
		{
			ps_exec(data, "rb", 1);
			rot_b--;
		}
		else if (rot_b < 0)
		{
			ps_exec(data, "rrb", 1);
			rot_b++;
		}
	}
}

t_uint	ps_calc_chunk_size(unsigned int n, float disorder)
{
	unsigned int	base;
	float			factor;
	unsigned int	chunk_size;
	unsigned int	max_chunk_size;

	if (n < 2)
		return (1);
	base = 2;
	while ((base + 1) * (base + 1) <= n)
		base++;
	factor = 0.5f + (1.5f * disorder);
	chunk_size = (unsigned int)((float)base * factor + 0.5f);
	max_chunk_size = n / 2;
	if (max_chunk_size < 4)
		max_chunk_size = 4;
	if (chunk_size < 4)
		return (4);
	if (chunk_size > max_chunk_size)
		return (max_chunk_size);
	return (chunk_size);
}

t_uint	ps_rot_cost(int rot_a, int rot_b)
{
	unsigned int	u_rot_a;
	unsigned int	u_rot_b;

	u_rot_a = ps_abs(rot_a);
	u_rot_b = ps_abs(rot_b);
	if ((rot_a >= 0 && rot_b >= 0) || (rot_a <= 0 && rot_b <= 0))
	{
		if (u_rot_a > u_rot_b)
			return (u_rot_a);
		else
			return (u_rot_b);
	}
	return (u_rot_a + u_rot_b);
}
