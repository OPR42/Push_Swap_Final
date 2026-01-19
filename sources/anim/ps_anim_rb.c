/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_rb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:37:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 21:37:58 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ps_anim_rb_longend(t_data *data, int frame, int len)
{
	char	*upwards;

	if (frame >= 14 && frame < 14 + len)
	{
		upwards = ps_read_element(data, 53, frame + 1);
		ps_put_spaces(data, 53, 67, frame + 1);
		if (frame < 13 + len)
		{
			ps_write_element(data, 53, frame, upwards);
			ps_paint12cells(data, 53, frame, '7');
		}
		free(upwards);
	}
}

void	ps_anim_rb_longloop(t_data *data, int frame, int len, char *up)
{
	if (data->display[25][53].c == U'╱')
	{
		if (frame > 14 && frame < 24)
		{
			up = ps_read_element(data, 53, frame);
			ps_put_spaces(data, 53, 67, frame);
			ps_write_element(data, 53, frame - 1, up);
			ps_paint12cells(data, 53, frame - 1, '7');
			free(up);
		}
		ps_anim_separator_opener(data, 23, frame - ((26 + len) / 4));
		if (frame > 28 && frame < 38)
		{
			up = ps_read_element(data, 53, frame);
			ps_put_spaces(data, 53, 67, frame);
			if (frame >= 30)
			{
				ps_write_element(data, 53, frame - 1, up);
				ps_paint12cells(data, 53, frame - 1, '7');
			}
			free(up);
		}
	}
	else
		ps_anim_rb_longend(data, frame, len);
}

void	ps_anim_rb_loop(t_data *data, int frm, int l, char *frst)
{
	if (frm < 13)
	{
		ps_write_element(data, 53 + frm, 14, frst);
		ps_anim_rx_colors(data, 32, frm);
		ps_paint12cells(data, 53 + frm, 14, '6');
	}
	else if (frm >= 13 && frm < 13 + l)
	{
		ps_write_element(data, 66, frm + 1, frst);
		if (frm > 13)
			ps_put_spaces(data, 66, 77, frm);
		ps_paint12cells(data, 66, frm + 1, '6');
	}
	else if (frm >= 13 + l && frm < 26 + l)
	{
		ps_write_element(data, 78 + l - frm, 13 + l, frst);
		ps_paint12cells(data, 78 + l - frm, 13 + l, '6');
		ps_anim_rx_colors(data, 32, frm - 12);
	}
}

void	ps_anim_rb(t_data *data)
{
	char	*first;
	int		frame;
	int		y;
	int		len;

	first = ps_read_element(data, 53, 14);
	ps_put_panel(data, PANELRB);
	len = 0;
	y = 14;
	while (y < 38)
		if (data->display[y++][59].c != U' ')
			len++;
	if (data->display[25][53].c == U'╱')
		len += 4;
	frame = 0;
	while (frame < 26 + len)
	{
		ps_anim_rb_loop(data, frame, len, first);
		ps_anim_rb_longloop(data, frame, len, "");
		ps_print_canvas(data, '7', 1, 0);
		frame++;
	}
	free(first);
}
