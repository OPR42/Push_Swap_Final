/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_rr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 00:01:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/16 00:01:58 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_len(t_data *data, int col)
{
	int		y;
	int		len;
	int		lcol;

	len = 0;
	lcol = col - 6;
	y = 14;
	while (y < 38)
		if (data->display[y++][col].c != U' ')
			len++;
	if (data->display[25][lcol].c == U'╱')
		len += 4;
	return (len);
}

static void	init_lens(t_data *data, int *len_a, int *len_b)
{
	*len_a = find_len(data, 20);
	*len_b = find_len(data, 59);
}

static void	launch_rr(t_data *data, int len)
{
	char	*first_a;
	char	*first_b;
	int		frame;
	int		len_a;
	int		len_b;

	first_a = ps_read_element(data, 14, 14);
	first_b = ps_read_element(data, 53, 14);
	init_lens (data, &len_a, &len_b);
	frame = 0;
	while (frame < 26 + len)
	{
		if (frame < 26 + len_a)
			ps_anim_ra_loop(data, frame, len_a, first_a);
		if (frame < 26 + len_b)
			ps_anim_rb_loop(data, frame, len_b, first_b);
		if (frame < 26 + len_a)
			ps_anim_ra_longloop(data, frame, len_a, "");
		if (frame < 26 + len_b)
			ps_anim_rb_longloop(data, frame, len_b, "");
		ps_print_canvas(data, '7', 1, 0);
		frame++;
	}
	free(first_a);
	free(first_b);
}

void	ps_anim_rr(t_data *data)
{
	int	len;

	if (find_len(data, 20) >= find_len(data, 59))
		len = find_len(data, 20);
	else
		len = find_len(data, 59);
	ps_put_panel(data, PANELRR);
	launch_rr(data, len);
}
