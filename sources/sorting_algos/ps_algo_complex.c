/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_complex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:32:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 20:25:30 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*static void	dummy_display(t_data *data)
{
	ps_stacks_rotate(data, 3, 0);
	ps_exec(data, "sa", 3);
	ps_stacks_rotate(data, -3, 0);
	ps_exec(data, "pb", 10);
	ps_stacks_rotate(data, 0, 3);
	ps_exec(data, "sb", 3);
	ps_stacks_rotate(data, 0, -3);
	ps_exec(data, "ss", 3);
	ps_stacks_rotate(data, 3, 3);
	ps_stacks_rotate(data, -3, -3);
	ps_stacks_rotate(data, 3, -3);
	ps_stacks_rotate(data, -3, 3);
	ps_exec(data, "pb", 15);
	ps_stacks_rotate(data, 2, 3);
	ps_stacks_rotate(data, -3, -2);
	ps_exec(data, "pa", 9);
	ps_exec(data, "sa", 2);
	ps_exec(data, "sb", 2);
	ps_exec(data, "ss", 3);
}

void	ps_algo_complex(t_data *data)
{
	data->algo_class = ps_strdup("Dummy O( +oo -1 )");
	data->algo_name = ps_strdup(" *** The cake is a lie *** ");
	dummy_display(data);
}*/

void	radix2(t_data *data, t_stack *hk, t_uint n, t_uint mask)
{
	unsigned int	i;
	int				bits;

	bits = 0;
	while (((n - 1) >> bits) != 0)
		bits++;
	while (bits-- > 0)
	{
		i = 0;
		while (i++ < n)
		{
			if ((hk->next->rank & mask) == 0)
				ps_exec(data, "pb", 1);
			else
				ps_exec(data, "ra", 1);
		}
		ps_exec(data, "pa", data->count_nb_b);
		mask <<= 1;
	}
}

void	ps_algo_complex(t_data *data)
{
	if (data->initial_disorder == 0)
		ps_algo_none(data);
	else
	{
		data->algo_class = ps_strdup("Complex O(n ℓn)");
		data->algo_name = ps_strdup("        Radix base2        ");
		radix2(data, data->stack_a_hook, data->count_nb_a, 1);
	}
}
