/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_benchview_stacks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 20:37:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 19:04:52 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	stack_a_short(t_data *data, unsigned int *y)
{
	data->stack_a_curr = data->stack_a_hook->next;
	while (*y <= 37)
	{
		ps_put_spaces(data, 15, 26, *y);
		if (data->count_nb_a >= *y - 13)
			ps_put_nbr_cent(data, data->stack_a_curr->value, 1500 + *y, '7');
		data->stack_a_curr = data->stack_a_curr->next;
		(*y)++;
	}
}

static void	stack_a_long(t_data *data, unsigned int *y)
{
	data->stack_a_curr = data->stack_a_hook->next;
	while (*y <= 23)
	{
		ps_put_spaces(data, 15, 26, *y);
		ps_put_nbr_cent(data, data->stack_a_curr->value, 1500 + *y, '7');
		data->stack_a_curr = data->stack_a_curr->next;
		(*y)++;
	}
	ps_put_separator(data, 14, data->count_nb_a - 19);
	data->stack_a_curr = data->stack_a_hook->previous;
	*y = 37;
	while (*y >= 29)
	{
		ps_put_spaces(data, 15, 26, *y);
		ps_put_nbr_cent(data, data->stack_a_curr->value, 1500 + *y, '7');
		data->stack_a_curr = data->stack_a_curr->previous;
		(*y)--;
	}
}

static void	stack_b_short(t_data *data, unsigned int *y)
{
	data->stack_b_curr = data->stack_b_hook->next;
	while (*y <= 37)
	{
		ps_put_spaces(data, 54, 65, *y);
		if (data->count_nb_b >= *y - 13)
			ps_put_nbr_cent(data, data->stack_b_curr->value, 5400 + *y, '7');
		data->stack_b_curr = data->stack_b_curr->next;
		(*y)++;
	}
}

static void	stack_b_long(t_data *data, unsigned int *y)
{
	data->stack_b_curr = data->stack_b_hook->next;
	while (*y <= 23)
	{
		ps_put_spaces(data, 54, 65, *y);
		ps_put_nbr_cent(data, data->stack_b_curr->value, 5400 + *y, '7');
		data->stack_b_curr = data->stack_b_curr->next;
		(*y)++;
	}
	ps_put_separator(data, 53, data->count_nb_b - 19);
	data->stack_b_curr = data->stack_b_hook->previous;
	*y = 37;
	while (*y >= 29)
	{
		ps_put_spaces(data, 54, 65, *y);
		ps_put_nbr_cent(data, data->stack_b_curr->value, 5400 + *y, '7');
		data->stack_b_curr = data->stack_b_curr->previous;
		(*y)--;
	}
}

void	ps_put_stacks(t_data *data, unsigned int y, unsigned int x)
{
	if (data->count_nb_a <= 24)
		stack_a_short(data, &y);
	else
		stack_a_long(data, &y);
	y = 14;
	if (data->count_nb_b <= 24)
		stack_b_short(data, &y);
	else
		stack_b_long(data, &y);
	ps_show_ballance_level(data, x);
}
