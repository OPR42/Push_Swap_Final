/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_helpers3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:20:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/21 11:20:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static unsigned int	seek_or_mark_grow(t_stack *hook, t_stack *probe, short mode)
{
	unsigned int	len;
	unsigned int	max;

	len = 1;
	max = probe->rank;
	if (mode == 1)
		probe->keep = 1;
	while (probe != hook)
	{
		if (probe->rank > max)
		{
			if (mode == 1)
				probe->keep = 1;
			len++;
			max = probe->rank;
		}
		probe = probe->next;
	}
	return (len);
}

t_uint	ps_mark_longest_grow(t_stack *hook)
{
	t_stack			*curr;
	t_stack			*max_node;
	unsigned int	len;
	unsigned int	max_len;

	curr = hook->next;
	max_len = 0;
	while (curr != hook)
	{
		curr->keep = 0;
		len = seek_or_mark_grow(hook, curr, 0);
		if (len > max_len)
		{
			max_len = len;
			max_node = curr;
		}
		curr = curr->next;
	}
	len = seek_or_mark_grow(hook, max_node, 1);
	return (len);
}

void	ps_mark_distances_to_top(t_data *data)
{
	t_stack			*curr;
	unsigned int	dist;

	dist = 0;
	curr = data->stack_a_hook->next;
	while (curr != data->stack_a_hook)
	{
		if (dist > data->count_nb_a / 2)
			curr->dist_top = dist - data->count_nb_a;
		else
			curr->dist_top = dist;
		dist++;
		curr = curr->next;
	}
	dist = 0;
	curr = data->stack_b_hook->next;
	while (curr != data->stack_b_hook)
	{
		if (dist > data->count_nb_b / 2)
			curr->dist_top = dist - data->count_nb_b;
		else
			curr->dist_top = dist;
		dist++;
		curr = curr->next;
	}
}

static t_stack	*min_rank_node(t_data *data, t_stack *hook)
{
	t_stack	*curr;
	t_stack	*min;

	data->k = data->k;
	curr = hook->next;
	min = curr;
	while (curr != hook)
	{
		if (curr->rank < min->rank)
			min = curr;
		curr = curr->next;
	}
	return (min);
}

void	ps_mark_cost_to_target(t_data *data, t_stack *hk_b, t_stack *hk_a)
{
	t_stack	*curr;
	t_stack	*probe;

	hk_a->rank = 4294967295;
	curr = hk_b->next;
	while (curr != hk_b)
	{
		curr->target = hk_a;
		probe = hk_a->next;
		while (probe != hk_a)
		{
			if (probe->rank > curr->rank && probe->rank < curr->target->rank)
				curr->target = probe;
			probe = probe->next;
		}
		if (curr->target == hk_a)
		{
			curr->target = min_rank_node(data, hk_a);
		}
		curr->target_cost = ps_rot_cost(curr->target->dist_top, curr->dist_top);
		curr = curr->next;
	}
	hk_a->rank = 0;
}
