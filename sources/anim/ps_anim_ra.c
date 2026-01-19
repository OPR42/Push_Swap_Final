/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_ra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:32:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 20:52:58 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ps_anim_ra_longend(t_data *data, int frame, int len)
{
	char	*upwards;

	if (frame >= 14 && frame < 14 + len)
	{
		upwards = ps_read_element(data, 14, frame + 1);
		ps_put_spaces(data, 14, 27, frame + 1);
		if (frame < 13 + len)
		{
			ps_write_element(data, 14, frame, upwards);
			ps_paint12cells(data, 14, frame, '7');
		}
		free(upwards);
	}
}

void	ps_anim_ra_longloop(t_data *data, int frame, int len, char *up)
{
	if (data->display[25][14].c == U'╱')
	{
		if (frame > 14 && frame < 24)
		{
			up = ps_read_element(data, 14, frame);
			ps_put_spaces(data, 14, 27, frame);
			ps_write_element(data, 14, frame - 1, up);
			ps_paint12cells(data, 14, frame - 1, '7');
			free(up);
		}
		ps_anim_separator_opener(data, 13, frame - ((26 + len) / 4));
		if (frame > 28 && frame < 38)
		{
			up = ps_read_element(data, 14, frame);
			ps_put_spaces(data, 14, 27, frame);
			if (frame >= 30)
			{
				ps_write_element(data, 14, frame - 1, up);
				ps_paint12cells(data, 14, frame - 1, '7');
			}
			free(up);
		}
	}
	else
		ps_anim_ra_longend(data, frame, len);
}

void	ps_anim_ra_loop(t_data *data, int frm, int l, char *frst)
{
	if (frm < 13)
	{
		ps_write_element(data, 14 - frm, 14, frst);
		ps_anim_rx_colors(data, 31, frm);
		ps_paint12cells(data, 14 - frm, 14, '6');
	}
	else if (frm >= 13 && frm < 13 + l)
	{
		ps_write_element(data, 2, frm + 1, frst);
		if (frm > 13)
			ps_put_spaces(data, 2, 13, frm);
		ps_paint12cells(data, 2, frm + 1, '6');
	}
	else if (frm >= 13 + l && frm < 26 + l)
	{
		ps_write_element(data, frm - 11 - l, 13 + l, frst);
		ps_paint12cells(data, frm - 11 - l, 13 + l, '6');
		ps_anim_rx_colors(data, 31, frm - 12);
	}
}

void	ps_anim_ra(t_data *data)
{
	char	*first;
	int		frame;
	int		y;
	int		len;

	first = ps_read_element(data, 14, 14);
	ps_put_panel(data, PANELRA);
	len = 0;
	y = 14;
	while (y < 38)
		if (data->display[y++][20].c != U' ')
			len++;
	if (data->display[25][14].c == U'╱')
		len += 4;
	frame = 0;
	while (frame < 26 + len)
	{
		ps_anim_ra_loop(data, frame, len, first);
		ps_anim_ra_longloop(data, frame, len, "");
		ps_print_canvas(data, '7', 1, 0);
		frame++;
	}
	free(first);
}
