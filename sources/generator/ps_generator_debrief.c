/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_generator_debrief.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 10:37:07 by orobert           #+#    #+#             */
/*   Updated: 2026/01/01 10:37:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_char_xy(t_gendata *data, char c, int xy, char color)
{
	data->display[xy % 100][xy / 100].color = color;
	data->display[xy % 100][xy / 100].c = c;
}

static void	put_bench_nbr(t_gendata *data, int n, int x, int y)
{
	long	nb;
	int		l;
	int		i;

	nb = n;
	l = ps_intlen(n) - 1;
	if (nb == 0)
		put_char_xy(data, '0', (x * 100) + y, '6');
	if (nb < 0)
	{
		put_char_xy(data, '-', ((x - l) * 100) + y, '6');
		nb = -nb;
	}
	i = l;
	while (nb > 0)
	{
		put_char_xy(data, '0' + (nb % 10), ((x - l + i) * 100) + y, '6');
		i--;
		nb /= 10;
	}
}

static void	build_canvas(t_gendata *data)
{
	const char	*bench;
	int			j;
	int			x;
	int			y;

	bench = GENBENCH;
	j = 0;
	y = 0;
	while (y < 15)
	{
		x = 0;
		while (x < 80)
		{
			if (x < 79)
				data->display[y][x].c = ps_utf8_next(&bench, 0);
			else
				data->display[y][79].c = '\n';
			data->display[y][x++].color = COLORGENBENCH[j++];
		}
		y++;
	}
}

static void	print_canvas(t_gendata *data, char color)
{
	int			x;
	int			y;
	uint32_t	c;

	y = 0;
	while (y < 15)
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

void	ps_gen_debrief(t_gendata *data)
{
	build_canvas(data);
	put_bench_nbr(data, data->quantity, 36, 11);
	put_bench_nbr(data, data->ops, 75, 11);
	put_bench_nbr(data, data->wanted_disorder * 100, 35, 12);
	put_bench_nbr(data, data->wanted_disorder, 32, 12);
	put_char_xy(data, '.', 3312, '6');
	put_char_xy(data, '%', 3612, '6');
	put_bench_nbr(data, (data->disorder * 10000) - 100, 74, 12);
	put_bench_nbr(data, (data->disorder * 1000) - 10, 73, 12);
	put_bench_nbr(data, (data->disorder * 100), 71, 12);
	put_char_xy(data, '.', 7212, '6');
	put_char_xy(data, '%', 7512, '6');
	print_canvas(data, '7');
}
