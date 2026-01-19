/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_instr_rrx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:21:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/12 12:21:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_rra(t_data *data, short alone)
{
	t_stack	*last;
	t_stack	*first;

	data->count_rra += alone;
	data->count_ops += alone;
	if (alone == 1 && data->bench_mode < 2)
		write (1, "rra\n", 4);
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (alone == 1 && data->bench_mode == 3)
		ps_display_benchview(data, 41);
	if (data->count_nb_a < 2)
		return ;
	data->stack_a_curr = data->stack_a_hook->previous->previous;
	last = data->stack_a_hook->previous;
	first = data->stack_a_hook->next;
	last->next = first;
	first->previous = last;
	last->previous = data->stack_a_hook;
	data->stack_a_hook->next = last;
	data->stack_a_hook->previous = data->stack_a_curr;
	data->stack_a_curr->next = data->stack_a_hook;
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}

void	ps_rrb(t_data *data, short alone)
{
	t_stack	*last;
	t_stack	*first;

	data->count_rrb += alone;
	data->count_ops += alone;
	if (alone == 1 && data->bench_mode < 2)
		write (1, "rrb\n", 4);
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (alone == 1 && data->bench_mode == 3)
		ps_display_benchview(data, 42);
	if (data->count_nb_b < 2)
		return ;
	data->stack_b_curr = data->stack_b_hook->previous->previous;
	last = data->stack_b_hook->previous;
	first = data->stack_b_hook->next;
	last->next = first;
	first->previous = last;
	last->previous = data->stack_b_hook;
	data->stack_b_hook->next = last;
	data->stack_b_hook->previous = data->stack_b_curr;
	data->stack_b_curr->next = data->stack_b_hook;
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}

void	ps_rrr(t_data *data)
{
	data->count_rrr += 1;
	data->count_ops += 1;
	if (data->bench_mode < 2)
		write (1, "rrr\n", 4);
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (data->bench_mode == 3)
		ps_display_benchview(data, 43);
	ps_rra(data, 0);
	ps_rrb(data, 0);
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}
