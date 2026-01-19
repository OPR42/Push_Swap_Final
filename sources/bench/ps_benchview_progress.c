/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_benchview_progress.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:36:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/24 13:36:56 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	display_order(t_data *data)
{
	const char		*bars;
	unsigned short	index;
	unsigned short	count_zeros;

	count_zeros = 0;
	index = 0;
	while (index < 23)
		if (data->order[index++] == 0)
			count_zeros++;
	index = 0;
	while (index < 23 - count_zeros)
	{
		bars = INCREASEBARS;
		ps_forward_utf8_string(&bars, data->order[index]);
		data->display[38][3 + index + count_zeros].c = ps_utf8_next(&bars, 0);
		index++;
	}
	index = 23;
	while (index < 46)
	{
		bars = INCREASEBARS;
		ps_forward_utf8_string(&bars, data->order[index]);
		data->display[38][31 + index].c = ps_utf8_next(&bars, 0);
		index++;
	}
}

static void	fill_order(t_data *data, t_stack *hook, t_uint idx, t_uint max_idx)
{
	t_stack			*curr;
	unsigned int	average;
	unsigned int	count_average;
	unsigned int	count;

	count = 0;
	average = 0;
	count_average = 0;
	curr = hook->next;
	while (curr != hook)
	{
		average += curr->rank;
		count_average++;
		count++;
		if (count > ((idx + 23 - max_idx) * data->count_nb) / 23
			|| curr->next == hook)
		{
			if (idx <= max_idx)
				data->order[idx++] = ((average / count_average) * 8
						/ (data->count_nb)) + 1;
			average = 0;
			count_average = 0;
		}
		curr = curr->next;
	}
}

static void	put_order(t_data *data)
{
	unsigned short	index;

	index = 0;
	while (index < 46)
	{
		data->order[index] = 0;
		index++;
	}
	fill_order(data, data->stack_a_hook, 0, 22);
	fill_order(data, data->stack_b_hook, 23, 45);
	display_order(data);
}

static void	put_clocks(t_data *data, unsigned int progress)
{
	if (progress >= 8 && progress < 16)
		data->display[13][35].c = U'◔';
	else if (progress >= 16 && progress < 25)
		data->display[13][35].c = U'◑';
	else if (progress >= 25 && progress < 33)
		data->display[13][35].c = U'◕';
	else if (progress >= 33)
		data->display[13][35].c = U'●';
	if (progress >= 42 && progress < 50)
		data->display[13][39].c = U'◔';
	else if (progress >= 50 && progress < 59)
		data->display[13][39].c = U'◑';
	else if (progress >= 59 && progress < 67)
		data->display[13][39].c = U'◕';
	else if (progress >= 67)
		data->display[13][39].c = U'●';
	if (progress >= 75 && progress < 83)
		data->display[13][43].c = U'◔';
	else if (progress >= 83 && progress < 92)
		data->display[13][43].c = U'◑';
	else if (progress >= 92 && progress < 100)
		data->display[13][43].c = U'◕';
	else if (progress >= 100)
		data->display[13][43].c = U'●';
}

void	ps_put_progress(t_data *data, long done, long mess, int x)
{
	mess = (ps_stack_not_progressive(data->stack_a_hook) - 1);
	done = (1000 * (data->initial_mess - (int)mess)) / data->initial_mess;
	done = (done * (data->count_nb_a + 1)) / (data->count_nb + 1);
	if (done > 1000)
		done = 1000;
	if (done > data->max_progress)
		data->max_progress = done;
	data->display[11][41].c = data->max_progress % 10 + '0';
	data->display[11][39].c = (data->max_progress / 10) % 10 + '0';
	data->display[11][38].c = (data->max_progress / 100) % 10 + '0';
	data->display[11][37].c = (data->max_progress / 1000) % 10 + '0';
	while (x < 52)
	{
		if (data->max_progress / (1000 / 24) > x - 28)
		{
			data->display[12][x].c = U'▮';
			data->display[12][x].color = '5';
		}
		else
			data->display[12][x].c = U'╌';
		x++;
	}
	put_clocks(data, data->max_progress / 10);
	put_order(data);
}
