/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:13:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/10 02:13:10 by orobert          ###   ########.fr       */
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

int	ps_sorting_done(t_data *data, t_stack *hka, t_stack *hkb)
{
	t_stack			*curr;
	short			done;
	unsigned int	nb;
	unsigned int	ops;

	nb = data->count_nb;
	ops = data->count_ops;
	done = 1;
	if (data->count_nb_a != data->count_nb || data->count_nb_b != 0)
		done = 0;
	if (hkb->next != hkb || hkb->previous != hkb)
		done = 0;
	curr = hka->next->next;
	while (curr != hka)
	{
		if (curr->value <= curr->previous->value)
			done = 0;
		curr = curr->next;
	}
	if (done == 1 && ((nb >= 100 && ops <= 700) || (nb >= 500 && ops <= 5500)))
		done = 2;
	return (done);
}

int	ps_stack_not_progressive(t_stack *hook)
{
	t_stack	*current;
	int		misplaced;

	misplaced = 0;
	current = hook->next;
	while (current != hook)
	{
		if (current->next == hook)
		{
			if (current->value > current->next->next->value)
				misplaced++;
		}
		else
		{
			if (current->value > current->next->value)
				misplaced++;
		}
		current = current->next;
	}
	return (misplaced);
}

float	ps_compute_disorder(t_data *data)
{
	t_stack			*temp;
	unsigned int	mistakes;
	unsigned int	total_pairs;

	mistakes = 0;
	total_pairs = 0;
	data->stack_a_curr = data->stack_a_hook->next;
	while (data->stack_a_curr->next != data->stack_a_hook)
	{
		temp = data->stack_a_curr->next;
		while (temp != data->stack_a_hook)
		{
			total_pairs++;
			if (data->stack_a_curr->value > temp->value)
				mistakes++;
			temp = temp->next;
		}
		data->stack_a_curr = data->stack_a_curr->next;
	}
	return ((float)mistakes / (float)total_pairs);
}
