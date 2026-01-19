/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_adaptive_bouncers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:07:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/20 16:07:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rot_a_to_push_pos(t_data *data, t_uint high, t_uint top, t_uint bot)
{
	t_stack			*curr;

	curr = data->stack_a_hook->next;
	while (curr != data->stack_a_hook)
	{
		if (curr->rank <= high && curr->keep != 1)
			break ;
		top++;
		curr = curr->next;
	}
	if (top >= data->count_nb_a)
		return (0);
	curr = data->stack_a_hook->previous;
	while (curr != data->stack_a_hook)
	{
		if (curr->rank <= high && curr->keep != 1)
			break ;
		bot++;
		curr = curr->previous;
	}
	if (top <= bot)
		ps_exec(data, "ra", top);
	else
		ps_exec(data, "rra", bot + 1);
	return (1);
}

void	ps_chunk_harvest(t_data *data, t_stack *hka, t_uint low, t_uint kp)
{
	unsigned int	tries;

	data->n = data->count_nb_a;
	data->chunk_size = ps_calc_chunk_size(data->n, data->initial_disorder) + 1;
	data->high = data->chunk_size - 1;
	while (data->count_nb_a > kp)
	{
		if (data->high >= data->n)
			data->high = data->n - 1;
		tries = 0;
		while (!rot_a_to_push_pos(data, data->high, 0, 0) && tries++ < data->n)
			data->high = (data->high + 1 < data->n) * (data->high + 1)
				+ (data->high + 1 >= data->n) * (data->n - 1);
		if (hka->next->keep == 1)
			break ;
		data->rank = hka->next->rank;
		ps_exec(data, "pb", 1);
		if (data->rank < low + (data->chunk_size / 10))
			ps_exec(data, "rb", 1);
		if (low < data->n)
			low++;
		(data->high)++;
	}
}

void	ps_simple_bouncer(t_data *data, t_stack *hka)
{
	t_stack			*curr;
	unsigned int	i;

	ps_stack_align_min_to_top(data, hka);
	ps_exec(data, "ra", 1);
	i = 1;
	while (i < data->count_nb_a)
	{
		curr = hka->next;
		if (curr->rank == hka->previous->rank + 1)
		{
			ps_exec(data, "ra", 1);
			i++;
		}
		else
			ps_exec(data, "pb", 1);
	}
}
