/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_benchview_basics.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 23:49:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 19:48:56 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_put_spaces(t_data *data, int x, int x_end, int y)
{
	while (x <= x_end)
	{
		if (data->display[y][x].c >= '0' && data->display[y][x].c <= '9')
		{
			data->display[y][x].c = ' ';
			data->display[y][x].color = '7';
		}
		if (data->display[y][x].c == '-' || data->display[y][x].c == '.')
		{
			data->display[y][x].c = ' ';
			data->display[y][x].color = '7';
		}
		x++;
	}
}

void	ps_put_nbr_cent(t_data *data, int n, int xy, char color)
{
	long	nb;
	int		len;
	int		i;
	int		char_xy;

	nb = n;
	len = ps_intlen(n);
	char_xy = (((xy / 100) + 5 - (len / 2)) * 100) + (xy % 100);
	if (nb == 0)
		ps_put_char_xy(data, '0', char_xy, color);
	if (nb < 0)
	{
		ps_put_char_xy(data, '-', char_xy, color);
		nb = -nb;
	}
	i = len - 1;
	while (nb > 0)
	{
		ps_put_char_xy(data, '0' + (nb % 10), char_xy + (i * 100), color);
		i--;
		nb /= 10;
	}
}

void	ps_show_ballance_level(t_data *data, unsigned int x)
{
	x = 28;
	while (x < 52)
	{
		if (x == 50 - (((data->count_nb_a) * 22) / data->count_nb))
		{
			data->display[38][x].c = U'⬤';
			data->display[38][x].color = '5';
		}
		else if (x == 51 - (((data->count_nb_a) * 22) / data->count_nb))
		{
			data->display[38][x].c = U' ';
			data->display[38][x].color = '3';
		}
		else
		{
			data->display[38][x].c = U'─';
			data->display[38][x].color = '3';
		}
		x++;
	}
}

void	ps_put_separator(t_data *data, int x, unsigned int count)
{
	const char	*separator;
	int			x_curr;
	int			y_curr;

	separator = SEPARATOR;
	y_curr = 24;
	while (y_curr < 29)
	{
		x_curr = x;
		while (x_curr < x + 13)
		{
			data->display[y_curr][x_curr].c = ps_utf8_next(&separator, 0);
			data->display[y_curr][x_curr].color = '3';
			x_curr++;
		}
		y_curr++;
	}
	ps_put_nbr_cent(data, count, ((x + 1) * 100) + 26, '6');
}

void	ps_huge_success(t_data *data)
{
	const char	*awesome;
	int			j;
	int			x;
	int			y;

	awesome = AWESOME;
	j = 0;
	y = 30;
	while (*awesome)
	{
		x = 26;
		while (x <= 53)
		{
			data->display[y][x].c = ps_utf8_next(&awesome, 0);
			data->display[y][x].color = COLORAWESOME[j];
			j++;
			x++;
		}
		y++;
	}
}
