/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:29:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 18:59:21 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_paint_zone_up(t_data *data, char ca, char cb, char cc)
{
	int	x;
	int	y;

	y = 11;
	while (y <= 38)
	{
		x = 2;
		while (x <= 77)
		{
			if (y > 13 && y < 16 && x > 2 && x < 40 && ca > '2' && ca <= '9')
				data->display[y][x].color = ca;
			if (y > 13 && y < 16 && x > 40 && x < 78 && cb > '2' && cb <= '9')
				data->display[y][x].color = cb;
			if (y >= 20 && y < 38 && x >= 28 && x <= 51)
				if (cc >= '0' && cc <= '9')
					data->display[y][x].color = cc;
			if (y > 10 && y < 39 && x > 1 && x < 79 && (cc == '1' || cc == '2'))
				if (data->display[y][x].color != '3')
					if (data->display[y][x].color != '7')
						data->display[y][x].color = cc;
			x++;
		}
		y++;
	}
}

void	ps_paint_zone_down(t_data *data, char ca, char cb)
{
	int	x;
	int	y;

	y = 29;
	x = 3;
	while (x <= 39)
		data->display[y][x++].color = ca;
	x = 41;
	while (x <= 77)
		data->display[y][x++].color = cb;
}

void	ps_anim_sx_colors(t_data *data, short op, int frame)
{
	if (op == 11 && (frame < 1 || frame > 12))
		ps_paint_zone_up(data, '6', '7', '0');
	else if (op == 11 && (frame < 3 || frame > 10))
		ps_paint_zone_up(data, '6', '7', '4');
	else if (op == 11)
		ps_paint_zone_up(data, '6', '7', '6');
	else if (op == 12 && (frame < 1 || frame > 12))
		ps_paint_zone_up(data, '7', '6', '0');
	else if (op == 12 && (frame < 3 || frame > 10))
		ps_paint_zone_up(data, '7', '6', '4');
	else if (op == 12)
		ps_paint_zone_up(data, '7', '6', '6');
	else if (op == 13 && (frame < 1 || frame > 12))
		ps_paint_zone_up(data, '6', '6', '0');
	else if (op == 13 && (frame < 3 || frame > 10))
		ps_paint_zone_up(data, '6', '6', '4');
	else if (op == 13)
		ps_paint_zone_up(data, '6', '6', '6');
}

void	ps_anim_rx_colors(t_data *data, short op, int frame)
{
	if (op == 31 && (frame < 1 || frame > 37))
		ps_paint_zone_up(data, '7', 'a', '0');
	else if (op == 31 && (frame < 3 || frame > 35))
		ps_paint_zone_up(data, '7', 'a', '4');
	else if (op == 31)
		ps_paint_zone_up(data, '7', 'a', '6');
	else if (op == 32 && (frame < 1 || frame > 37))
		ps_paint_zone_up(data, 'a', '7', '0');
	else if (op == 32 && (frame < 3 || frame > 35))
		ps_paint_zone_up(data, 'a', '7', '4');
	else if (op == 32)
		ps_paint_zone_up(data, 'a', '7', '6');
	else if (op == 33 && (frame < 1 || frame > 37))
		ps_paint_zone_up(data, '7', '7', '0');
	else if (op == 33 && (frame < 3 || frame > 35))
		ps_paint_zone_up(data, '7', '7', '4');
	else if (op == 33)
		ps_paint_zone_up(data, '7', '7', '6');
}

void	ps_paint12cells(t_data *data, int x, int y, char color)
{
	int	i;

	i = 0;
	while (i < 12)
		data->display[y][x + i++].color = color;
}
