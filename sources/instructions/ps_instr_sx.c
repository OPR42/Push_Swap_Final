/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_instr_sx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:20:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/12 12:20:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_sa(t_data *data, short alone)
{
	t_stack	*first;
	t_stack	*second;

	data->count_sa += alone;
	data->count_ops += alone;
	if (alone == 1 && data->bench_mode < 2)
		write (1, "sa\n", 3);
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (alone == 1 && data->bench_mode == 3)
		ps_display_benchview(data, 11);
	if (data->count_nb_a < 2)
		return ;
	data->stack_a_curr = data->stack_a_hook->next->next->next;
	first = data->stack_a_hook->next;
	second = data->stack_a_hook->next->next;
	data->stack_a_hook->next = second;
	second->next = first;
	first->next = data->stack_a_curr;
	data->stack_a_curr->previous = first;
	first->previous = second;
	second->previous = data->stack_a_hook;
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}

void	ps_sb(t_data *data, short alone)
{
	t_stack	*first;
	t_stack	*second;

	data->count_sb += alone;
	data->count_ops += alone;
	if (alone == 1 && data->bench_mode < 2)
		write (1, "sb\n", 3);
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (alone == 1 && data->bench_mode == 3)
		ps_display_benchview(data, 12);
	if (data->count_nb_b < 2)
		return ;
	data->stack_b_curr = data->stack_b_hook->next->next->next;
	first = data->stack_b_hook->next;
	second = data->stack_b_hook->next->next;
	data->stack_b_hook->next = second;
	second->next = first;
	first->next = data->stack_b_curr;
	data->stack_b_curr->previous = first;
	first->previous = second;
	second->previous = data->stack_b_hook;
	if (alone == 1 && data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}

void	ps_ss(t_data *data)
{
	data->count_ss += 1;
	data->count_ops += 1;
	if (data->bench_mode < 2)
		write (1, "ss\n", 3);
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 0);
	if (data->bench_mode == 3)
		ps_display_benchview(data, 13);
	ps_sa(data, 0);
	ps_sb(data, 0);
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 0);
}

static void	ps_exec_loop(t_data *data, char *instruction)
{
	if (ps_strncmp(instruction, "sa", 3) == 0)
		ps_sa(data, 1);
	else if (ps_strncmp(instruction, "sb", 3) == 0)
		ps_sb(data, 1);
	else if (ps_strncmp(instruction, "ss", 3) == 0)
		ps_ss(data);
	else if (ps_strncmp(instruction, "pa", 3) == 0)
		ps_pa(data);
	else if (ps_strncmp(instruction, "pb", 3) == 0)
		ps_pb(data);
	else if (ps_strncmp(instruction, "ra", 3) == 0)
		ps_ra(data, 1);
	else if (ps_strncmp(instruction, "rb", 3) == 0)
		ps_rb(data, 1);
	else if (ps_strncmp(instruction, "rr", 3) == 0)
		ps_rr(data);
	else if (ps_strncmp(instruction, "rra", 4) == 0)
		ps_rra(data, 1);
	else if (ps_strncmp(instruction, "rrb", 4) == 0)
		ps_rrb(data, 1);
	else if (ps_strncmp(instruction, "rrr", 4) == 0)
		ps_rrr(data);
}

void	ps_exec(t_data *data, char *instruction, unsigned int quantity)
{
	unsigned int	i;

	i = 0;
	while (i < quantity)
	{
		ps_exec_loop(data, instruction);
		i++;
	}
}
