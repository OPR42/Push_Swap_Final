/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:45:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 19:07:03 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	show_gap(t_data *data, int x_start, int y_start, char *s)
{
	int			g;
	int			x;
	int			y;
	const char	*p;

	g = 0;
	x = x_start;
	y = y_start;
	p = s;
	while (*p)
	{
		if (g >= 13 && y == y_start)
		{
			y++;
			x = x_start;
		}
		data->display[y][x++].c = ps_utf8_next(&p, 0);
		g++;
	}
}

void	ps_anim_separator_opener(t_data *data, int pos, int step)
{
	int	x;

	if (step < 1 || step > 3)
		return ;
	if (pos / 10 < 1 || pos / 10 > 2 || pos % 10 < 1 || pos % 10 > 3)
		return ;
	x = ((pos / 10) * 39) - 25;
	if ((pos % 10 == 1 || pos % 10 == 3) && step == 1)
		show_gap(data, x, 24, "    ╱   ╲    ╱▔▔▔     ▔▔▔╲");
	else if ((pos % 10 == 1 || pos % 10 == 3) && step == 2)
		show_gap(data, x, 24, "   ▎     ▕   ╱▔▔       ▔▔╲");
	else if ((pos % 10 == 1 || pos % 10 == 3) && step == 3)
		show_gap(data, x, 24, " ╲         ╱ ╱▔         ▔╲");
	if ((pos % 10 == 2 || pos % 10 == 3) && step == 1)
		show_gap(data, x, 27, "╲▁▁▁     ▁▁▁╱    ╲   ╱    ");
	else if ((pos % 10 == 2 || pos % 10 == 3) && step == 2)
		show_gap(data, x, 27, "╲▁▁       ▁▁╱   ▎     ▕   ");
	else if ((pos % 10 == 2 || pos % 10 == 3) && step == 3)
		show_gap(data, x, 27, "╲▁         ▁╱ ╱         ╲ ");
}

void	ps_put_panel(t_data *data, const char *panel)
{
	int			x;
	int			y;
	const char	*p;

	y = 19;
	p = panel;
	while (*p)
	{
		x = 28;
		while (x <= 51)
			data->display[y][x++].c = ps_utf8_next(&p, 0);
		y++;
	}
}
