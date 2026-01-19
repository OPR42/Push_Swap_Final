/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:43:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/09 20:43:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_wait(int interval)
{
	volatile unsigned long	i;

	i = 0;
	while (i < DELAY * interval)
		i++;
}

char	*ps_strdup(const char *s)
{
	unsigned int	len;
	unsigned int	i;
	char			*dest;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ps_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ps_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	if (ps_init_stacks(data) == -1)
		return (-1);
	data->algo_type = 0;
	data->bench_mode = 0;
	data->count_nb = 0;
	data->count_nb_a = 0;
	data->count_nb_b = 0;
	data->count_ops = 0;
	data->count_sa = 0;
	data->count_sb = 0;
	data->count_ss = 0;
	data->count_pa = 0;
	data->count_pb = 0;
	data->count_ra = 0;
	data->count_rb = 0;
	data->count_rr = 0;
	data->count_rra = 0;
	data->count_rrb = 0;
	data->count_rrr = 0;
	data->max_progress = 0;
	data->done = 0;
	return (0);
}
