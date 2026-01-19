/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:05:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/12 15:05:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_data *data, t_stack *hook)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;

	a = hook->next->rank;
	b = hook->next->next->rank;
	c = hook->next->next->next->rank;
	if (a > b && a > c && data->count_nb_a == 3)
		ps_exec(data, "ra", 1);
	else if (b > a && b > c && data->count_nb_a == 3)
		ps_exec(data, "rra", 1);
	a = hook->next->rank;
	b = hook->next->next->rank;
	if (a > b)
		ps_exec(data, "sa", 1);
}

void	sort_five(t_data *data, t_stack *ha, t_stack *hb)
{
	unsigned int	count_nb;

	count_nb = data->count_nb;
	while (data->count_nb_a > 3)
	{
		if (ps_sorting_done(data, ha, hb) >= 1)
			return ;
		else if (ha->next->rank == 0 || (ha->next->rank == 1 && count_nb == 5))
			ps_exec(data, "pb", 1);
		else
			ps_exec(data, "ra", 1);
	}
	sort_three(data, ha);
	if (hb->next->rank == 1 && data->count_nb_b >= 2)
		ps_exec(data, "pa", 1);
	else if (data->count_nb_b >= 2)
	{
		ps_exec(data, "sb", 1);
		ps_exec(data, "pa", 1);
	}
	ps_exec(data, "pa", 1);
}

void	cocktail_shaker(t_data *data)
{
	unsigned int	i;
	unsigned int	range;
	short			way;
	t_stack			*hook;

	hook = data->stack_a_hook;
	range = data->count_nb_a - 1 - data->count_nb_a % 2;
	way = 1;
	while (ps_stack_not_progressive(hook) > 1)
	{
		i = 0;
		while (i < range)
		{
			if (ps_is_target(hook->next, hook->next->next, hook) == 1)
				ps_exec(data, "sa", 1);
			if (ps_stack_not_progressive(hook) <= 1)
				break ;
			ps_stacks_rotate(data, way, 0);
			i++;
		}
		way = -way;
		if (way < 0)
			range--;
	}
	ps_stack_align_min_to_top(data, hook);
}

void	ps_algo_simple(t_data *data)
{
	if (data->initial_disorder == 0)
		ps_algo_none(data);
	else
	{
		data->algo_class = ps_strdup("Simple O(n²)");
		data->algo_name = ps_strdup("      Cocktail Shaker      ");
		cocktail_shaker(data);
	}
}
