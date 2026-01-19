/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_sx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:08:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 12:08:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ps_anim_sa_loop(t_data *data, int frame, char *a, char *b)
{
	if (frame < 7)
	{
		ps_write_element(data, 14 - frame, 14, a);
		ps_paint12cells(data, 14 - frame, 14, '6');
		ps_write_element(data, 14 + frame, 15, b);
		ps_paint12cells(data, 14 + frame, 15, '6');
	}
	if (frame == 7)
	{
		ps_put_spaces(data, 4, 40, 14);
		ps_put_spaces(data, 4, 40, 15);
		ps_paint_zone_up(data, '6', '7', '6');
	}
	if (frame >= 7)
	{
		ps_write_element(data, 28 - frame, 14, b);
		ps_paint12cells(data, 28 - frame, 14, '6');
		ps_write_element(data, 0 + frame, 15, a);
		ps_paint12cells(data, 0 + frame, 15, '6');
	}
}

static void	ps_anim_sb_loop(t_data *data, int frame, char *a, char *b)
{
	if (frame < 7)
	{
		ps_write_element(data, 53 + frame, 14, a);
		ps_paint12cells(data, 53 + frame, 14, '6');
		ps_write_element(data, 53 - frame, 15, b);
		ps_paint12cells(data, 53 - frame, 15, '6');
	}
	if (frame == 7)
	{
		ps_put_spaces(data, 41, 77, 14);
		ps_put_spaces(data, 41, 77, 15);
		ps_paint_zone_up(data, '7', '6', '6');
	}
	if (frame >= 7)
	{
		ps_write_element(data, 39 + frame, 14, b);
		ps_paint12cells(data, 39 + frame, 14, '6');
		ps_write_element(data, 67 - frame, 15, a);
		ps_paint12cells(data, 67 - frame, 15, '6');
	}
}

void	ps_anim_sa(t_data *data)
{
	char	*first;
	char	*second;
	int		frame;

	first = ps_read_element(data, 14, 14);
	second = ps_read_element(data, 14, 15);
	ps_put_panel(data, PANELSA);
	frame = 0;
	while (frame < 14)
	{
		ps_anim_sa_loop(data, frame, first, second);
		ps_anim_sx_colors(data, 11, frame);
		ps_print_canvas(data, '7', 1, 0);
		frame++;
	}
	free(first);
	free(second);
}

void	ps_anim_sb(t_data *data)
{
	char	*first;
	char	*second;
	int		frame;

	first = ps_read_element(data, 53, 14);
	second = ps_read_element(data, 53, 15);
	ps_put_panel(data, PANELSB);
	frame = 0;
	while (frame < 14)
	{
		ps_anim_sb_loop(data, frame, first, second);
		ps_anim_sx_colors(data, 12, frame);
		ps_print_canvas(data, '7', 1, 0);
		frame++;
	}
	free(first);
	free(second);
}

void	ps_anim_ss(t_data *data)
{
	char	*firsta;
	char	*seconda;
	char	*firstb;
	char	*secondb;
	int		frame;

	firsta = ps_read_element(data, 14, 14);
	seconda = ps_read_element(data, 14, 15);
	firstb = ps_read_element(data, 53, 14);
	secondb = ps_read_element(data, 53, 15);
	ps_put_panel(data, PANELSS);
	frame = 0;
	while (frame < 14)
	{
		ps_anim_sa_loop(data, frame, firsta, seconda);
		ps_anim_sb_loop(data, frame, firstb, secondb);
		ps_anim_sx_colors(data, 13, frame);
		ps_print_canvas(data, '7', 1, 0);
		frame++;
	}
	free(firsta);
	free(seconda);
	free(firstb);
	free(secondb);
}
