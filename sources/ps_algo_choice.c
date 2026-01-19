/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_choice.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:13:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/10 02:13:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_algo_none(t_data *data)
{
	data->algo_class = ps_strdup("None - O(0)");
	data->algo_name = ps_strdup("Already sorted - Just relax");
}

int	ps_sorting_done(t_data *data, t_stack *hka, t_stack *hkb)
{
	t_stack			*curr;
	short			done;
	unsigned int	nb;
	unsigned int	ops;

	nb = data->count_nb;
	ops = data->count_ops;
	done = 1;
	if (data->count_nb_a != data->count_nb || data->count_nb_b != 0)
		done = 0;
	if (hkb->next != hkb || hkb->previous != hkb)
		done = 0;
	curr = hka->next->next;
	while (curr != hka)
	{
		if (curr->value <= curr->previous->value)
			done = 0;
		curr = curr->next;
	}
	if (done == 1 && ((nb >= 100 && ops <= 700) || (nb >= 500 && ops <= 5500)))
		done = 2;
	return (done);
}

int	ps_stack_not_progressive(t_stack *hook)
{
	t_stack	*current;
	int		misplaced;

	misplaced = 0;
	current = hook->next;
	while (current != hook)
	{
		if (current->next == hook)
		{
			if (current->value > current->next->next->value)
				misplaced++;
		}
		else
		{
			if (current->value > current->next->value)
				misplaced++;
		}
		current = current->next;
	}
	return (misplaced);
}

float	ps_compute_disorder(t_data *data)
{
	t_stack			*temp;
	unsigned int	mistakes;
	unsigned int	total_pairs;

	mistakes = 0;
	total_pairs = 0;
	data->stack_a_curr = data->stack_a_hook->next;
	while (data->stack_a_curr->next != data->stack_a_hook)
	{
		temp = data->stack_a_curr->next;
		while (temp != data->stack_a_hook)
		{
			total_pairs++;
			if (data->stack_a_curr->value > temp->value)
				mistakes++;
			temp = temp->next;
		}
		data->stack_a_curr = data->stack_a_curr->next;
	}
	return ((float)mistakes / (float)total_pairs);
}

void	ps_algochoice(t_data *data)
{
	if (data->bench_mode >= 2)
		ps_display_benchview(data, 99);
	data->initial_disorder = ps_compute_disorder(data);
	data->initial_mess = ps_stack_not_progressive(data->stack_a_hook);
	if (data->algo_type == 0)
		data->algo_type = 5;
	if (data->bench_mode == 2 || data->bench_mode == 3)
		write(1, "\033[2J\033[?25l", 10);
	if (data->algo_type == 1)
		ps_algo_simple(data);
	else if (data->algo_type == 2)
		ps_algo_medium(data);
	else if (data->algo_type == 3)
		ps_algo_complex(data);
	else if (data->algo_type == 4)
		yavuz_sultan(data, data->stack_a_hook, data->stack_b_hook, 0);
	else if (data->algo_type == 5)
		ps_algo_adaptive(data);
	if (data->bench_mode == 1)
		ps_display_bench(data);
	else if (data->bench_mode == 2 || data->bench_mode == 3)
		ps_display_benchview(data, 100);
	data->done = 1;
}
