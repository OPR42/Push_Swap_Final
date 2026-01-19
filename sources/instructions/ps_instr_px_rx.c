/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_instr_px_rx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:20:37 by orobert           #+#    #+#             */
/*   Updated: 2025/12/12 12:20:40 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_pb(t_data *data)
{
	t_stack	*moved;

	data->count_pb += 1;
	data->count_ops += 1;
	if (data->bench_mode < 2)
		write (1, "pb\n", 3);
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (data->bench_mode == 3)
		ps_display_benchview(data, 22);
	if (data->count_nb_a < 1)
		return ;
	moved = data->stack_a_hook->next;
	data->stack_a_hook->next->next->previous = data->stack_a_hook;
	data->stack_a_hook->next = data->stack_a_hook->next->next;
	data->count_nb_a -= 1;
	data->stack_b_curr = data->stack_b_hook->next;
	data->stack_b_hook->next = moved;
	moved->next = data->stack_b_curr;
	data->stack_b_curr->previous = moved;
	moved->previous = data->stack_b_hook;
	data->count_nb_b += 1;
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}

void	ps_pa(t_data *data)
{
	t_stack	*moved;

	data->count_pa += 1;
	data->count_ops += 1;
	if (data->bench_mode < 2)
		write (1, "pa\n", 3);
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (data->bench_mode == 3)
		ps_display_benchview(data, 21);
	if (data->count_nb_b < 1)
		return ;
	moved = data->stack_b_hook->next;
	data->stack_b_hook->next->next->previous = data->stack_b_hook;
	data->stack_b_hook->next = data->stack_b_hook->next->next;
	data->count_nb_b -= 1;
	data->stack_a_curr = data->stack_a_hook->next;
	data->stack_a_hook->next = moved;
	moved->next = data->stack_a_curr;
	data->stack_a_curr->previous = moved;
	moved->previous = data->stack_a_hook;
	data->count_nb_a += 1;
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}

void	ps_ra(t_data *data, short alone)
{
	t_stack	*last;
	t_stack	*first;

	data->count_ra += alone;
	data->count_ops += alone;
	if (alone == 1 && data->bench_mode < 2)
		write (1, "ra\n", 3);
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (alone == 1 && data->bench_mode == 3)
		ps_display_benchview(data, 31);
	if (data->count_nb_a < 2)
		return ;
	data->stack_a_curr = data->stack_a_hook->next->next;
	last = data->stack_a_hook->previous;
	first = data->stack_a_hook->next;
	last->next = first;
	first->previous = last;
	first->next = data->stack_a_hook;
	data->stack_a_hook->previous = first;
	data->stack_a_hook->next = data->stack_a_curr;
	data->stack_a_curr->previous = data->stack_a_hook;
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}

void	ps_rb(t_data *data, short alone)
{
	t_stack	*last;
	t_stack	*first;

	data->count_rb += alone;
	data->count_ops += alone;
	if (alone == 1 && data->bench_mode < 2)
		write (1, "rb\n", 3);
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (alone == 1 && data->bench_mode == 3)
		ps_display_benchview(data, 32);
	if (data->count_nb_b < 2)
		return ;
	data->stack_b_curr = data->stack_b_hook->next->next;
	last = data->stack_b_hook->previous;
	first = data->stack_b_hook->next;
	last->next = first;
	first->previous = last;
	first->next = data->stack_b_hook;
	data->stack_b_hook->previous = first;
	data->stack_b_hook->next = data->stack_b_curr;
	data->stack_b_curr->previous = data->stack_b_hook;
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}

void	ps_rr(t_data *data)
{
	data->count_rr += 1;
	data->count_ops += 1;
	if (data->bench_mode < 2)
		write (1, "rr\n", 3);
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (data->bench_mode == 3)
		ps_display_benchview(data, 33);
	ps_ra(data, 0);
	ps_rb(data, 0);
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}
