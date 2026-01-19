/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_chainlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:13:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/10 00:13:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	send_nodes(t_data *data, int value)
{
	t_stack	*node;

	data->stack_a_curr = data->stack_a_hook;
	while (data->stack_a_curr->next)
	{
		data->stack_a_curr = data->stack_a_curr->next;
		if (data->stack_a_curr->value == value)
			return (-1);
	}
	node = (t_stack *)malloc(sizeof(*node));
	if (!node)
		return (-1);
	node->value = value;
	node->next = NULL;
	node->previous = data->stack_a_curr;
	data->stack_a_curr->next = node;
	data->stack_a_curr = data->stack_a_curr->next;
	data->count_nb += 1;
	data->count_nb_a += 1;
	return (0);
}

void	ps_stack_clear(t_stack *hook)
{
	t_stack	*current;
	t_stack	*next;

	current = hook;
	if (current->previous)
	{
		current->previous->next = NULL;
		current->previous = NULL;
	}
	while (current)
	{
		next = current->next;
		if (current->previous)
		{
			current->previous->next = NULL;
			current->previous = NULL;
		}
		free(current);
		current = next;
	}
	hook = NULL;
}

int	ps_init_stacks(t_data *data)
{
	data->stack_a_hook = (t_stack *)malloc(sizeof(*data->stack_a_hook));
	if (!data->stack_a_hook)
		return (-1);
	data->stack_a_hook->next = NULL;
	data->stack_b_hook = (t_stack *)malloc(sizeof(*data->stack_b_hook));
	if (!data->stack_b_hook)
		return (-1);
	data->stack_b_hook->next = data->stack_b_hook;
	data->stack_b_hook->previous = data->stack_b_hook;
	return (0);
}
