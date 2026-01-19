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

static unsigned int	find_distance_to_min(t_stack *hook)
{
	unsigned int	i;
	int				min;
	unsigned int	distance;
	t_stack			*curr;

	i = 0;
	distance = 0;
	min = INT_MAX;
	curr = hook->next;
	while (curr != hook)
	{
		if (curr->value < min)
		{
			min = curr->value;
			distance = i;
		}
		i++;
		curr = curr->next;
	}
	return (distance);
}

static void	ps_do_stack_align(t_data *data, t_stack *hook, int dist, int count)
{
	int	i;

	i = 0;
	if (dist > 0 && dist <= count / 2)
	{
		while (i++ < dist)
		{
			if (hook == data->stack_b_hook)
				ps_exec(data, "rb", 1);
			else
				ps_exec(data, "ra", 1);
		}
	}
	else if (dist > 0)
	{
		dist = count - dist;
		while (i++ < dist)
		{
			if (hook == data->stack_b_hook)
				ps_exec(data, "rrb", 1);
			else
				ps_exec(data, "rra", 1);
		}
	}
}

void	ps_stack_align_min_to_top(t_data *data, t_stack *hook)
{
	unsigned int	distance;
	unsigned int	count_nb_stack;

	if (hook == data->stack_b_hook)
		count_nb_stack = data->count_nb_b;
	else
		count_nb_stack = data->count_nb_a;
	distance = find_distance_to_min(hook);
	ps_do_stack_align(data, hook, distance, count_nb_stack);
}

int	ps_is_target(t_stack *a, t_stack *b, t_stack *hook)
{
	int		min;
	int		max;
	t_stack	*curr;

	min = 2147483647;
	max = -2147483648;
	curr = hook->next;
	while (curr != hook)
	{
		if (curr->value < min)
			min = curr->value;
		if (curr->value > max)
			max = curr->value;
		curr = curr->next;
	}
	if (a->value > b->value && (a->value != max || b->value != min))
		return (1);
	return (0);
}

int	ps_send_recon(t_stack *hook)
{
	t_stack	*fw;
	t_stack	*rw;
	int		forward;
	int		backward;

	fw = hook->next;
	rw = hook->previous;
	forward = 1;
	backward = 1;
	if (ps_is_target (rw, fw, hook) == 1)
		return (-1);
	while (fw->next != hook && rw->previous != hook)
	{
		fw = fw->next;
		rw = rw->previous;
		backward++;
		if (fw->next == hook || rw->previous == hook)
			return (0);
		if (ps_is_target (fw, fw->next, hook) == 1)
			return (forward);
		if (ps_is_target (rw, rw->next, hook) == 1)
			return (-backward);
		forward++;
	}
	return (0);
}
