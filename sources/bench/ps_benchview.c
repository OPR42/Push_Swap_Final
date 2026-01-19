/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_benchview.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 19:41:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/14 19:41:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	build_largecanvas(t_data *data)
{
	const char	*benchview;
	int			j;
	int			x;
	int			y;

	benchview = BENCHVIEW;
	j = 0;
	y = 0;
	while (y < 50)
	{
		x = 0;
		while (x < 80)
		{
			if (x < 79)
				data->display[y][x].c = ps_utf8_next(&benchview, 0);
			else
				data->display[y][79].c = '\n';
			if (x < 2 || x > 77 || y < 2 || y > 7)
				data->display[y][x].color = COLORBENCHVIEW[j];
			j++;
			x++;
		}
		y++;
	}
}

static void	fill_largecanvas(t_data *data, float disorder)
{
	ps_put_bench_nbr(data, data->count_nb, 36, 40);
	ps_put_bench_nbr(data, (disorder * 10000) - 100, 74, 40);
	ps_put_bench_nbr(data, (disorder * 1000) - 10, 73, 40);
	ps_put_bench_nbr(data, (disorder * 100), 71, 40);
	ps_put_char_xy(data, '.', 7240, '6');
	ps_put_char_xy(data, '%', 7540, '6');
	ps_put_bench_nbr(data, data->count_ops, 36, 41);
	ps_put_algo(data, data->algo_class, 75, 41);
	ps_put_bench_nbr(data, data->count_changes, 22, 43);
	ps_put_algo(data, data->algo_name, 52, 43);
	ps_put_bench_nbr(data, data->count_moves, 75, 43);
	ps_put_bench_nbr(data, data->count_sa, 17, 45);
	ps_put_bench_nbr(data, data->count_sb, 17, 46);
	ps_put_bench_nbr(data, data->count_ss, 17, 47);
	ps_put_bench_nbr(data, data->count_pa, 36, 45);
	ps_put_bench_nbr(data, data->count_pb, 36, 46);
	ps_put_bench_nbr(data, data->count_ra, 55, 45);
	ps_put_bench_nbr(data, data->count_rb, 55, 46);
	ps_put_bench_nbr(data, data->count_rr, 55, 47);
	ps_put_bench_nbr(data, data->count_rra, 75, 45);
	ps_put_bench_nbr(data, data->count_rrb, 75, 46);
	ps_put_bench_nbr(data, data->count_rrr, 75, 47);
	ps_put_stacks(data, 14, 0);
	ps_put_progress(data, 0, 0, 28);
	ps_put_large_numbers(data);
}

void	ps_print_canvas(t_data *data, char color, int x, int y)
{
	uint32_t	c;

	if (x != 0)
		ps_scroll_banner(data, 0, 0);
	ps_wait(x);
	write(1, "\033[H", 3);
	while (y < 50)
	{
		x = 0;
		while (x < 80)
		{
			c = data->display[y][x++].c;
			if (color != data->display[y][x - 1].color && c != (uint32_t) ' ')
			{
				color = data->display[y][x - 1].color;
				write(1, "\033[0;1;3", 7);
				write(1, &color, 1);
				write(1, "m", 1);
			}
			ps_write_unicode(1, c);
		}
		y++;
	}
	write(1, "\033[0m", 4);
}

static void	ps_put_debrief(t_data *data, char color, int x, short done)
{
	const char	*panel;

	done = ps_sorting_done(data, data->stack_a_hook, data->stack_b_hook);
	if (done >= 1)
	{
		panel = SUCCESS;
		color = '2';
	}
	else
	{
		panel = FAIL;
		color = '1';
	}
	while (x <= 51)
	{
		data->display[11][x].color = color;
		data->display[12][x++].color = color;
	}
	ps_paint_zone_up(data, '7', '7', color);
	ps_put_panel(data, panel);
	if (done >= 2)
		ps_huge_success(data);
}

void	ps_display_benchview(t_data *data, int step)
{
	if ((step <= 10 || step >= 100) && step != 99)
	{
		build_largecanvas(data);
		ps_count_changes_moves(data);
		fill_largecanvas(data, data->initial_disorder);
	}
	else if (step == 99)
	{
		build_largecanvas(data);
		ps_init_banner(data);
	}
	else
		ps_anim_choose(data, step);
	if (step == 100)
		ps_put_debrief(data, '7', 28, 0);
	if (data->bench_mode == 3 || (step > 10 && step < 80))
		ps_print_canvas(data, '7', 1, 0);
	else
		ps_print_canvas(data, '7', 0, 0);
}
