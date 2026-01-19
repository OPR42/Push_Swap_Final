/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_read_input_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:43:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/09 20:43:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*ps_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len1 = ps_strlen(s1);
	len2 = ps_strlen(s2);
	res = (char *)malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

static char	*add_buffer(char *s1, char *s2)
{
	char	*out;

	if (!s1 && s2)
		return (ps_strdup(s2));
	if (!s1 && !s2)
		return (NULL);
	out = ps_strjoin(s1, s2);
	free(s1);
	return (out);
}

char	*ps_read_array(int fd, char *array)
{
	char		*buf;
	ssize_t		r;

	buf = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
	{
		free(array);
		return (NULL);
	}
	r = 1;
	while (r > 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
			break ;
		buf[r] = '\0';
		array = add_buffer(array, buf);
		if (!array)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (array);
}

t_uint	ps_array_len(char **array)
{
	unsigned int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}
