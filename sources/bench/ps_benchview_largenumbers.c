/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_benchview_largenumbers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 21:13:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/25 21:13:56 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_large_digit(t_data *data, short digit, t_uint xy, char color)
{
	const char		*largedigits;
	int				i;
	int				j;
	unsigned int	x;
	unsigned int	y;

	largedigits = LARGEDIGITS;
	x = xy / 100;
	y = xy % 100;
	ps_forward_utf8_string(&largedigits, digit * 3);
	j = 0;
	while (j < 3)
	{
		i = 0;
		while (i < 3)
		{
			data->display[y + j][x + i].c = ps_utf8_next(&largedigits, 0);
			data->display[y + j][x + i].color = color;
			i++;
		}
		if (j < 2)
			ps_forward_utf8_string(&largedigits, 27);
		j++;
	}
}

static void	put_large_cent_unumber(t_data *data, t_uint n, int xxy, char color)
{
	unsigned int	base_xy;
	unsigned int	mid;
	int				len;
	int				i;

	len = ps_intlen(n);
	mid = ((xxy % 10000 / 100 - xxy / 10000 + 1) / 2);
	base_xy = (((xxy / 10000 + mid - (len * 3 / 2)) - 1) * 100) + xxy % 100;
	if (xxy % 10000 / 100 - xxy / 10000 + 1 >= len * 3)
	{
		if (n == 0)
			put_large_digit(data, 0, base_xy, color);
		i = len - 1;
		while (n > 0)
		{
			put_large_digit(data, n % 10, base_xy + (i * 300), color);
			i--;
			n /= 10;
		}
	}
	else
		ps_put_nbr_cent(data, n,
			(xxy / 10000 + mid - 6) * 100 + xxy % 100 + 1, color);
}

void	ps_put_large_numbers(t_data *data)
{
	put_large_cent_unumber(data, data->count_ops, 295216, '7');
	put_large_cent_unumber(data, data->count_nb_a, 51311, '6');
	put_large_cent_unumber(data, data->count_nb_b, 677611, '6');
}
