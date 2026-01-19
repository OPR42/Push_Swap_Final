/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_helpers4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:20:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/21 11:20:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	trust_me_this_is_not_sorting(t_data *data, int *tab, int i, int j)
{
	t_stack	*curr;
	int		tmp;

	curr = data->stack_a_hook->next;
	while ((unsigned int)i < data->count_nb)
	{
		tab[i++] = curr->value;
		curr = curr->next;
	}
	while ((unsigned int)j < data->count_nb - 1)
	{
		i = 0;
		while ((unsigned int)i < data->count_nb - 1 - (unsigned int)j)
		{
			if (tab[i] > tab[i + 1])
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}

void	ps_set_ranks(t_data *data, unsigned int i, unsigned int j)
{
	int		*tab;
	t_stack	*curr;

	tab = (int *)malloc(data->count_nb * sizeof(int));
	if (!tab)
		return ;
	trust_me_this_is_not_sorting(data, tab, i, j);
	curr = data->stack_a_hook->next;
	j = 0;
	while (j < data->count_nb)
	{
		i = 0;
		while (tab[i] != curr->value)
			i++;
		curr->rank = i;
		curr = curr->next;
		j++;
	}
	free(tab);
}
