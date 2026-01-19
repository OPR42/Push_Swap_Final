/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_launch_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:13:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/10 02:13:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_clean_checker(t_data *data)
{
	if (data->instructions)
		ps_free_all(data->instructions, ps_array_len(data->instructions));
	ps_stack_clear(data->stack_a_hook);
	ps_stack_clear(data->stack_b_hook);
}

void	ps_algo_exec(t_data *data)
{
	unsigned int	i;

	data->algo_class = ps_strdup("Check operations");
	data->algo_name = ps_strdup(" ⟸ ⟪ Check in progress ⟫⟹  ");
	if (!data->instructions)
		return ;
	i = 0;
	while (data->instructions[i] && data->instructions[i + 1])
		ps_exec(data, data->instructions[i++], 1);
}

static short	is_valid_instruction(char *s)
{
	short	valid;

	valid = 0;
	if (ps_strncmp(s, "sa", 3) == 0 || ps_strncmp(s, "sb", 3) == 0)
		valid = 1;
	else if (ps_strncmp(s, "ss", 3) == 0)
		valid = 1;
	else if (ps_strncmp(s, "pa", 3) == 0 || ps_strncmp(s, "pb", 3) == 0)
		valid = 1;
	else if (ps_strncmp(s, "ra", 3) == 0 || ps_strncmp(s, "rb", 3) == 0)
		valid = 1;
	else if (ps_strncmp(s, "rra", 4) == 0 || ps_strncmp(s, "rrb", 4) == 0)
		valid = 1;
	else if (ps_strncmp(s, "rr", 3) == 0 || ps_strncmp(s, "rrr", 4) == 0)
		valid = 1;
	return (valid);
}

int	ps_read_instructions(t_data *data)
{
	char			*array;
	unsigned int	i;

	array = NULL;
	array = ps_read_array(0, array);
	data->instructions = ps_split(array, '\n');
	free(array);
	if (!data->instructions)
		return (0);
	i = 0;
	while (data->instructions[i] && data->instructions[i + 1])
	{
		if (is_valid_instruction(data->instructions[i]) != 1)
			return (-1);
		i++;
	}
	data->instr_count = i;
	return (i);
}

void	ps_algolaunch(t_data *data)
{
	if (data->bench_mode >= 2)
		ps_display_checkbenchview(data, 99);
	data->initial_disorder = ps_compute_disorder(data);
	data->initial_mess = ps_stack_not_progressive(data->stack_a_hook);
	if (data->bench_mode == 2 || data->bench_mode == 3)
		write(1, "\033[2J\033[?25l", 10);
	ps_algo_exec(data);
	if (data->bench_mode == 1)
		ps_display_checkbench(data);
	else if (data->bench_mode == 2 || data->bench_mode == 3)
		ps_display_checkbenchview(data, 100);
	else if (ps_sorting_done(data, data->stack_a_hook, data->stack_b_hook) >= 1)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	if (data->bench_mode == 2 || data->bench_mode == 3)
		write(1, "\033[?25h", 6);
}
