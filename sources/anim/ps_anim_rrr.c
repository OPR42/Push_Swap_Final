/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_rrr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:30:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/16 18:30:58 by opr              ###   ########.fr       */
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

static void	launch_rrr(t_data *data, int len)
{
	char	*last_a;
	char	*last_b;
	int		frame;
	int		len_a;
	int		len_b;

	init_lens (data, &len_a, &len_b);
	last_a = ps_read_element(data, 14, 13 + len_a);
	last_b = ps_read_element(data, 53, 13 + len_b);
	frame = 0;
	while (frame < 26 + len)
	{
		if (frame < 26 + len_a)
			ps_anim_rra_loop(data, frame, len_a, last_a);
		if (frame < 26 + len_b)
			ps_anim_rrb_loop(data, frame, len_b, last_b);
		if (frame < 26 + len_a)
			ps_anim_rra_longloop(data, frame, len_a, "");
		if (frame < 26 + len_b)
			ps_anim_rrb_longloop(data, frame, len_b, "");
		ps_print_canvas(data, '7', 1, 0);
		frame++;
	}
	free(last_a);
	free(last_b);
}

void	ps_anim_rrr(t_data *data)
{
	int	len;

	if (find_len(data, 20) >= find_len(data, 59))
		len = find_len(data, 20);
	else
		len = find_len(data, 59);
	ps_put_panel(data, PANELRRR);
	launch_rrr(data, len);
}
