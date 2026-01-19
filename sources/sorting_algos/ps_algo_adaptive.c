/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_adaptive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:07:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/20 16:07:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	compute_averages(t_data *data, t_uint keep)
{
	t_stack			*curr;
	unsigned int	i;
	unsigned int	tot_top;
	unsigned int	tot_bot;
	int				median;

	curr = data->stack_a_hook->next;
	i = 0;
	tot_top = 0;
	tot_bot = 0;
	while (curr != data->stack_a_hook)
	{
		if (i++ < (data->count_nb - keep) / 2 && curr->keep != 1)
			tot_top += curr->rank;
		else if (curr->keep != 1)
			tot_bot += curr->rank;
		curr = curr->next;
	}
	median = (tot_top + tot_bot) / (data->count_nb - keep);
	if (tot_bot >= tot_top)
		return (median);
	else
		return (-median);
}

static void	push_nokeep_median_pivot(t_data *data, t_stack *hka, t_uint keep)
{
	int	median;

	median = compute_averages(data, keep);
	while (data->count_nb_a > keep)
	{
		if (hka->next->keep == 1)
			ps_exec(data, "ra", 1);
		else
		{
			if (median >= 0 && hka->next->rank <= (unsigned int)median)
				ps_exec(data, "pb", 1);
			else if (median < 0 && hka->next->rank > ps_abs(median))
				ps_exec(data, "pb", 1);
			else
			{
				ps_exec(data, "pb", 1);
				if (hka->next->keep == 1 && data->count_nb_a > keep)
					ps_exec(data, "rr", 1);
				else if (data->count_nb_b > 1)
					ps_exec(data, "rb", 1);
			}
		}
	}
}

static void	bring_back_cheapest(t_data *data, t_stack *hka, t_stack *hkb)
{
	t_stack	*cheapest;
	t_stack	*curr;

	ps_mark_distances_to_top(data);
	ps_mark_cost_to_target(data, hkb, hka);
	curr = hkb->next;
	cheapest = curr;
	while (curr != hkb)
	{
		if (curr->target_cost < cheapest->target_cost)
			cheapest = curr;
		curr = curr->next;
	}
	ps_stacks_rotate(data, cheapest->target->dist_top, cheapest->dist_top);
	ps_exec(data, "pa", 1);
}

void	yavuz_sultan(t_data *data, t_stack *hka, t_stack *hkb, t_uint keep)
{
	if (data->algo_type == 4)
	{
		data->algo_class = ps_strdup("Custom O(n ℓn)");
		data->algo_name = ps_strdup(" ★★  Yavuz Sultan Selim ★★ ");
	}
	if (data->initial_disorder >= 0.5 || data->algo_type == 4)
	{
		keep = ps_mark_longest_grow(hka);
		push_nokeep_median_pivot(data, hka, keep);
	}
	else if (data->initial_disorder >= 0.2 && data->initial_disorder < 0.5)
	{
		keep = ps_mark_longest_grow(hka);
		ps_chunk_harvest(data, hka, 0, keep);
	}
	else if (data->initial_disorder < 0.2)
		ps_simple_bouncer(data, hka);
	while (data->count_nb_b > 0)
		bring_back_cheapest(data, hka, hkb);
	ps_stack_align_min_to_top(data, hka);
}

void	ps_algo_adaptive(t_data *data)
{
	if (data->initial_disorder == 0)
		ps_algo_none(data);
	else if (data->count_nb <= 3)
	{
		data->algo_class = ps_strdup("Adaptive O(n)");
		data->algo_name = ps_strdup("     One-Two for Three     ");
		sort_three(data, data->stack_a_hook);
	}
	else if (data->count_nb <= 5)
	{
		data->algo_class = ps_strdup("Adaptive O(2n)");
		data->algo_name = ps_strdup("        Double Five        ");
		sort_five(data, data->stack_a_hook, data->stack_b_hook);
	}
	else
	{
		if (data->initial_disorder < 0.2)
			data->algo_class = ps_strdup("Adaptive O(n²)");
		else if (data->initial_disorder >= 0.2 && data->initial_disorder < 0.5)
			data->algo_class = ps_strdup("Adaptive O(n √n)");
		else if (data->initial_disorder >= 0.5)
			data->algo_class = ps_strdup("Adaptive O(n ℓn)");
		data->algo_name = ps_strdup(" ★★  Yavuz Sultan Selim ★★ ");
		yavuz_sultan(data, data->stack_a_hook, data->stack_b_hook, 0);
	}
}
