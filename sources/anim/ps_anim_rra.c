/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_rra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:20:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/16 12:20:58 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ps_anim_rra_longend(t_data *data, int frame, int len)
{
	char	*downwards;

	if (frame >= 15 && frame < 14 + len)
	{
		downwards = ps_read_element(data, 14, 27 + len - frame);
		ps_put_spaces(data, 14, 27, 27 + len - frame);
		if (frame < 27 + len)
		{
			ps_write_element(data, 14, 28 + len - frame, downwards);
			ps_paint12cells(data, 14, 28 + len - frame, '7');
		}
		free(downwards);
	}
}

void	ps_anim_rra_longloop(t_data *data, int frame, int len, char *down)
{
	if (data->display[25][14].c == U'╱')
	{
		if (frame > 15 && frame < 24)
		{
			down = ps_read_element(data, 14, 52 - frame);
			ps_put_spaces(data, 14, 27, 52 - frame);
			ps_write_element(data, 14, 53 - frame, down);
			ps_paint12cells(data, 14, 53 - frame, '7');
			free(down);
		}
		ps_anim_separator_opener(data, 13, frame - ((26 + len) / 4));
		if (frame > 28 && frame < 39)
		{
			down = ps_read_element(data, 14, 52 - frame);
			ps_put_spaces(data, 14, 27, 52 - frame);
			if (frame >= 30)
			{
				ps_write_element(data, 14, 53 - frame, down);
				ps_paint12cells(data, 14, 53 - frame, '7');
			}
			free(down);
		}
	}
	else
		ps_anim_rra_longend(data, frame, len);
}

void	ps_anim_rra_loop(t_data *data, int frm, int l, char *lst)
{
	if (frm < 13)
	{
		ps_write_element(data, 14 - frm, 13 + l, lst);
		ps_anim_rx_colors(data, 31, frm);
		ps_paint12cells(data, 14 - frm, 13 + l, '6');
	}
	else if (frm >= 13 && frm < 13 + l)
	{
		ps_write_element(data, 2, 26 + l - frm, lst);
		if (frm > 13)
			ps_put_spaces(data, 2, 15, 27 + l - frm);
		ps_paint12cells(data, 2, 26 + l - frm, '6');
	}
	else if (frm >= 13 + l && frm < 26 + l)
	{
		ps_write_element(data, frm - 11 - l, 14, lst);
		ps_anim_rx_colors(data, 31, frm - 12);
		ps_paint12cells(data, frm - 11 - l, 14, '6');
	}
}

void	ps_anim_rra(t_data *data)
{
	char	*last;
	int		frame;
	int		y;
	int		len;

	ps_put_panel(data, PANELRRA);
	len = 0;
	y = 14;
	while (y < 38)
		if (data->display[y++][20].c != U' ')
			len++;
	if (data->display[25][14].c == U'╱')
		len += 4;
	frame = 0;
	last = ps_read_element(data, 14, 13 + len);
	while (frame < 26 + len)
	{
		ps_anim_rra_loop(data, frame, len, last);
		ps_anim_rra_longloop(data, frame, len, "");
		ps_print_canvas(data, '7', 1, 0);
		frame++;
	}
	free(last);
}
