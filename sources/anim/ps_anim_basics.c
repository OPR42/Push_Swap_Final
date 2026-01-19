/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_anim_basics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opr <opr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:24:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/15 19:46:02 by opr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*ps_read_element(t_data *data, int x, int y)
{
	int		i;
	char	*element;

	element = (char *)malloc(13 * sizeof(char));
	if (!element)
		return (0);
	i = 0;
	while (i < 12)
	{
		element[i] = data->display[y][x + i].c;
		i++;
	}
	element[i] = '\0';
	return (element);
}

void	ps_write_element(t_data *data, int x, int y, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		data->display[y][x + i].c = str[i];
		i++;
	}
	if (data->display[y][x + i].c >= '0' && data->display[y][x + i].c <= '9')
		data->display[y][x + i].c = ' ';
}

void	ps_anim_choose(t_data *data, int step)
{
	if (step == 11)
		ps_anim_sa(data);
	else if (step == 12)
		ps_anim_sb(data);
	else if (step == 13)
		ps_anim_ss(data);
	else if (step == 21)
		ps_anim_pa(data);
	else if (step == 22)
		ps_anim_pb(data);
	else if (step == 31)
		ps_anim_ra(data);
	else if (step == 32)
		ps_anim_rb(data);
	else if (step == 33)
		ps_anim_rr(data);
	else if (step == 41)
		ps_anim_rra(data);
	else if (step == 42)
		ps_anim_rrb(data);
	else if (step == 43)
		ps_anim_rrr(data);
}
