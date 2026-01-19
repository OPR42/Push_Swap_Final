/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_px.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:46:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 18:52:14 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ps_anim_px_colors(t_data *data, short op, int frame)
{
	if (op == 21 && (frame < 1 || frame > 37))
		ps_paint_zone_up(data, '7', '7', '0');
	else if (op == 21 && (frame < 3 || frame > 35))
		ps_paint_zone_up(data, '7', '7', '4');
	else if (op == 21)
		ps_paint_zone_up(data, '7', '7', '6');
	else if (op == 22 && (frame < 1 || frame > 37))
		ps_paint_zone_up(data, '7', '7', '0');
	else if (op == 22 && (frame < 3 || frame > 35))
		ps_paint_zone_up(data, '7', '7', '4');
	else if (op == 22)
		ps_paint_zone_up(data, '7', '7', '6');
}

void	ps_anim_pa(t_data *data)
{
	char	*first;
	int		frame;

	first = ps_read_element(data, 53, 14);
	ps_put_panel(data, PANELPA);
	frame = 0;
	while (frame < 39)
	{
		ps_write_element(data, 53 - frame, 14, first);
		ps_anim_pa_a_down(data, frame);
		ps_anim_pa_b_up(data, frame);
		ps_anim_px_colors(data, 21, frame);
		ps_paint12cells(data, 53 - frame, 14, '6');
		ps_print_canvas(data, '7', 1, 0);
		frame++;
	}
	free(first);
}

void	ps_anim_pb(t_data *data)
{
	char	*first;
	int		frame;

	first = ps_read_element(data, 14, 14);
	ps_put_panel(data, PANELPB);
	frame = 0;
	while (frame < 39)
	{
		ps_write_element(data, 14 + frame, 14, first);
		ps_anim_pb_a_up(data, frame);
		ps_anim_pb_b_down(data, frame);
		ps_anim_px_colors(data, 22, frame);
		ps_paint12cells(data, 14 + frame, 14, '6');
		ps_print_canvas(data, '7', 1, 0);
		frame++;
	}
	free(first);
}
