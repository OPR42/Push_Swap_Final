/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_px_stacks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:45:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 19:07:03 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_anim_pa_a_down(t_data *data, int frame)
{
	char	*downwards;

	if (data->display[25][14].c == U'╱')
	{
		if (frame > 14 && frame < 24)
		{
			downwards = ps_read_element(data, 14, 37 - frame);
			ps_put_spaces(data, 14, 28, 37 - frame);
			ps_write_element(data, 14, 38 - frame, downwards);
			free(downwards);
		}
		ps_anim_separator_opener(data, 11, frame - 11);
	}
	else
	{
		if (frame >= 1 && frame < 24)
		{
			downwards = ps_read_element(data, 14, 37 - frame);
			ps_put_spaces(data, 14, 28, 37 - frame);
			ps_write_element(data, 14, 38 - frame, downwards);
			free(downwards);
		}
	}
}

void	ps_anim_pa_b_up(t_data *data, int frame)
{
	char	*upwards;

	if (data->display[25][53].c == U'╱')
	{
		if (frame > 14 && frame < 24)
		{
			upwards = ps_read_element(data, 53, frame);
			ps_put_spaces(data, 53, 67, frame);
			if (frame <= 23)
				ps_write_element(data, 53, frame - 1, upwards);
			free(upwards);
		}
		ps_anim_separator_opener(data, 21, frame - 11);
	}
	else
	{
		if (frame > 14 && frame < 38)
		{
			upwards = ps_read_element(data, 53, frame);
			ps_put_spaces(data, 53, 67, frame);
			if (frame <= 37)
				ps_write_element(data, 53, frame - 1, upwards);
			free(upwards);
		}
	}
}

void	ps_anim_pb_a_up(t_data *data, int frame)
{
	char	*upwards;

	if (data->display[25][14].c == U'╱')
	{
		if (frame > 14 && frame < 24)
		{
			upwards = ps_read_element(data, 14, frame);
			ps_put_spaces(data, 14, 28, frame);
			if (frame <= 23)
				ps_write_element(data, 14, frame - 1, upwards);
			free(upwards);
		}
		ps_anim_separator_opener(data, 11, frame - 11);
	}
	else
	{
		if (frame > 14 && frame < 38)
		{
			upwards = ps_read_element(data, 14, frame);
			ps_put_spaces(data, 14, 28, frame);
			if (frame <= 37)
				ps_write_element(data, 14, frame - 1, upwards);
			free(upwards);
		}
	}
}

void	ps_anim_pb_b_down(t_data *data, int frame)
{
	char	*downwards;

	if (data->display[25][53].c == U'╱')
	{
		if (frame > 14 && frame < 24)
		{
			downwards = ps_read_element(data, 53, 37 - frame);
			ps_put_spaces(data, 53, 67, 37 - frame);
			ps_write_element(data, 53, 38 - frame, downwards);
			free(downwards);
		}
		ps_anim_separator_opener(data, 21, frame - 11);
	}
	else
	{
		if (frame >= 1 && frame < 24)
		{
			downwards = ps_read_element(data, 53, 37 - frame);
			ps_put_spaces(data, 53, 67, 37 - frame);
			ps_write_element(data, 53, 38 - frame, downwards);
			free(downwards);
		}
	}
}
