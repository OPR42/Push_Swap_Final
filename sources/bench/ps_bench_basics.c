/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_bench_basics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:02:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/12 22:02:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_put_algo(t_data *data, const char *algo, int x, int y)
{
	const char	*text;
	int			len;
	int			i;

	text = algo;
	len = ps_utf8_strlen(algo);
	i = 0;
	while (i < len)
	{
		data->display[y][x + 1 - len + i].color = '6';
		data->display[y][x + 1 - len + i].c = ps_utf8_next(&text, 0);
		i++;
	}
}

void	ps_put_char_xy(t_data *data, char c, int xy, char color)
{
	data->display[xy % 100][xy / 100].color = color;
	data->display[xy % 100][xy / 100].c = c;
}

void	ps_put_bench_nbr(t_data *data, int n, int x, int y)
{
	long	nb;
	int		len;
	int		i;

	nb = n;
	len = ps_intlen(n) - 1;
	if (nb == 0)
		ps_put_char_xy(data, '0', (x * 100) + y, '6');
	if (nb < 0)
	{
		ps_put_char_xy(data, '-', ((x - len) * 100) + y, '6');
		nb = -nb;
	}
	i = len;
	while (nb > 0)
	{
		ps_put_char_xy(data, '0' + (nb % 10), ((x - len + i) * 100) + y, '6');
		i--;
		nb /= 10;
	}
}

void	ps_count_changes_moves(t_data *data)
{
	data->count_changes = data->count_sa + data->count_sb + data->count_ss;
	data->count_changes += data->count_pa + data->count_pb;
	data->count_moves = data->count_ra + data->count_rb + data->count_rr;
	data->count_moves += data->count_rra + data->count_rrb + data->count_rrr;
}
