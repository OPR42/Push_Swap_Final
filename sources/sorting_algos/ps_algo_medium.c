/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_medium.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:01:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/20 16:01:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rot_a_to_push_pos(t_data *data, t_uint high, t_uint top, t_uint bot)
{
	t_stack			*curr;

	curr = data->stack_a_hook->next;
	while (curr != data->stack_a_hook)
	{
		if (curr->rank <= high)
			break ;
		top++;
		curr = curr->next;
	}
	if (top >= data->count_nb_a)
		return ;
	curr = data->stack_a_hook->previous;
	while (curr != data->stack_a_hook)
	{
		if (curr->rank <= high)
			break ;
		bot++;
		curr = curr->previous;
	}
	if (top <= bot)
		ps_exec(data, "ra", top);
	else
		ps_exec(data, "rra", bot + 1);
}

static void	back_to_a(t_data *data, t_stack *hkb, t_uint pos, t_uint best_pos)
{
	unsigned int	best_rank;
	t_stack			*curr;

	while (data->count_nb_b > 0)
	{
		pos = 0;
		best_pos = 0;
		best_rank = 0;
		curr = hkb->next;
		while (curr != hkb)
		{
			if (curr->rank > best_rank)
			{
				best_rank = curr->rank;
				best_pos = pos;
			}
			pos++;
			curr = curr->next;
		}
		if (best_pos <= data->count_nb_b / 2)
			ps_exec(data, "rb", best_pos);
		else
			ps_exec(data, "rrb", data->count_nb_b - best_pos);
		ps_exec(data, "pa", 1);
	}
}

void	dynamic_chunk(t_data *data, t_stack *hka, t_stack *hkb, t_uint low)
{
	data->n = data->count_nb_a;
	data->chunk_size = ps_calc_chunk_size(data->n, data->initial_disorder) + 1;
	data->high = data->chunk_size - 1;
	while (data->count_nb_a > 3)
	{
		if (data->high >= data->n)
			data->high = data->n - 1;
		data->effective_high = data->high;
		if (data->effective_high >= data->n - 3)
			data->effective_high = data->n - 4;
		if (data->effective_high < low)
			break ;
		rot_a_to_push_pos(data, data->effective_high, 0, 0);
		data->rank = hka->next->rank;
		ps_exec(data, "pb", 1);
		if (data->rank < low + (data->chunk_size / 10))
			ps_exec(data, "rb", 1);
		if (low < data->n)
			low++;
		(data->high)++;
	}
	sort_three(data, hka);
	back_to_a(data, hkb, 0, 0);
}

void	ps_algo_medium(t_data *data)
{
	if (data->initial_disorder == 0)
		ps_algo_none(data);
	else
	{
		data->algo_class = ps_strdup("Medium O(n √n)");
		data->algo_name = ps_strdup("       Dynamic Chunk       ");
		dynamic_chunk(data, data->stack_a_hook, data->stack_b_hook, 0);
	}
}
