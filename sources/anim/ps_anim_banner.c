/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_view_banner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:20:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/17 13:20:58 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_init_banner(t_data *data)
{
	int				x;
	int				y;
	int				j;

	y = 0;
	j = 0;
	while (y < 50)
	{
		x = 0;
		while (x < 80)
		{
			data->display[y][x].pass = 0;
			if (x >= 2 && x <= 77 && y >= 2 && y <= 7)
				data->display[y][x].color = COLORBENCHVIEW[j];
			j++;
			x++;
		}
		y++;
	}
}

void	ps_init_checkbanner(t_data *data)
{
	int				x;
	int				y;
	int				j;

	y = 0;
	j = 0;
	while (y < 50)
	{
		x = 0;
		while (x < 80)
		{
			data->display[y][x].pass = 0;
			if (x >= 2 && x <= 77 && y >= 2 && y <= 7)
				data->display[y][x].color = CHECKERCOLORBENCHVIEW[j];
			j++;
			x++;
		}
		y++;
	}
}

void	ps_scroll_banner(t_data *data, int x, int y)
{
	y = 2;
	while (y <= 7)
	{
		x = 9;
		while (x <= 70)
		{
			if (data->display[y][x].pass < 16)
				data->display[y][x].pass++;
			else
			{
				data->display[y][x].pass = 0;
				if (data->display[y][x].color == '6')
					data->display[y][x].color = '7';
				else if (data->display[y][x].color == '4')
					data->display[y][x].color = '6';
				else if (data->display[y][x].color == '5')
					data->display[y][x].color = '4';
				else if (data->display[y][x].color == '7')
					data->display[y][x].color = '5';
			}
			x++;
		}
		y++;
	}
}
