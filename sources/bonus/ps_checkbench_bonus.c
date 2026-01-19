/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_checkbench_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:02:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/12 22:02:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	build_canvas(t_data *data)
{
	const char	*bench;
	int			j;
	int			x;
	int			y;

	bench = CHECKERBENCH;
	j = 0;
	y = 0;
	while (y < 21)
	{
		x = 0;
		while (x < 80)
		{
			if (x < 79)
				data->display[y][x].c = ps_utf8_next(&bench, 0);
			else
				data->display[y][79].c = '\n';
			data->display[y][x].color = COLORBENCH[j++];
			x++;
		}
		y++;
	}
}

static void	fill_canvas(t_data *data, float disorder)
{
	ps_put_bench_nbr(data, data->count_nb, 36, 11);
	ps_put_bench_nbr(data, (disorder * 10000) - 100, 74, 11);
	ps_put_bench_nbr(data, (disorder * 1000) - 10, 73, 11);
	ps_put_bench_nbr(data, (disorder * 100), 71, 11);
	ps_put_char_xy(data, '.', 7211, '6');
	ps_put_char_xy(data, '%', 7511, '6');
	ps_put_bench_nbr(data, data->count_ops, 36, 12);
	ps_put_algo(data, data->algo_class, 75, 12);
	ps_put_bench_nbr(data, data->count_changes, 22, 14);
	ps_put_algo(data, data->algo_name, 52, 14);
	ps_put_bench_nbr(data, data->count_moves, 75, 14);
	ps_put_bench_nbr(data, data->count_sa, 17, 16);
	ps_put_bench_nbr(data, data->count_sb, 17, 17);
	ps_put_bench_nbr(data, data->count_ss, 17, 18);
	ps_put_bench_nbr(data, data->count_pa, 36, 16);
	ps_put_bench_nbr(data, data->count_pb, 36, 17);
	ps_put_bench_nbr(data, data->count_ra, 55, 16);
	ps_put_bench_nbr(data, data->count_rb, 55, 17);
	ps_put_bench_nbr(data, data->count_rr, 55, 18);
	ps_put_bench_nbr(data, data->count_rra, 75, 16);
	ps_put_bench_nbr(data, data->count_rrb, 75, 17);
	ps_put_bench_nbr(data, data->count_rrr, 75, 18);
}

static void	print_canvas(t_data *data, char color)
{
	int			x;
	int			y;
	uint32_t	c;

	y = 0;
	while (y < 21)
	{
		x = 0;
		while (x < 80)
		{
			c = data->display[y][x].c;
			if (color != data->display[y][x].color && c != (uint32_t) ' ')
			{
				color = data->display[y][x].color;
				write(2, "\033[0;1;3", 7);
				write(2, &color, 1);
				write(2, "m", 1);
			}
			ps_write_unicode(2, c);
			x++;
		}
		y++;
	}
	write(2, "\033[0m", 4);
}

void	ps_checkdebrief(t_data *data, unsigned int x, unsigned int y)
{
	char	*algo_name;
	char	*base;
	char	color;

	if (ps_sorting_done(data, data->stack_a_hook, data->stack_b_hook) >= 1)
	{
		algo_name = ps_strdup("✅ Effective✌ sequence ✅ ");
		color = '2';
	}
	else
	{
		algo_name = ps_strdup(" ❌ Wrong ⛔ sequence ❌  ");
		color = '1';
	}
	if (!algo_name)
		return ;
	base = algo_name;
	while (x < 53)
	{
		data->display[y][x].c = ps_utf8_next((const char **)&algo_name, 0);
		data->display[y][x++].color = color;
	}
	free(base);
}

void	ps_display_checkbench(t_data *data)
{
	build_canvas(data);
	ps_count_changes_moves(data);
	fill_canvas(data, data->initial_disorder);
	ps_checkdebrief(data, 27, 14);
	print_canvas(data, '7');
}
