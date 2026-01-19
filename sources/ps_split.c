/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:43:07 by orobert           #+#    #+#             */
/*   Updated: 2025/12/09 20:43:10 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*ps_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	s_len = ps_strlen(s);
	if (start >= s_len)
		return (ps_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static void	seek_limits(char const *s, char c, size_t *start, size_t *end)
{
	while (s[*start] == c)
		*start = *start + 1;
	*end = *start;
	while (s[*end] && s[*end] != c)
		*end = *end + 1;
}

void	ps_free_all(char **tab, size_t j)
{
	if (!tab)
		return ;
	while (j > 0)
		free(tab[--j]);
	free(tab);
}

char	**ps_split(char const *s, char c)
{
	char	**tab;
	size_t	start;
	size_t	end;
	size_t	j;

	if (!s)
		return (NULL);
	tab = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	j = 0;
	start = 0;
	while (s[start])
	{
		seek_limits(s, c, &start, &end);
		if (end > start)
		{
			tab[j++] = ps_substr(s, start, end - start);
			if (!tab[j - 1])
				return (ps_free_all(tab, j - 1), NULL);
		}
		start = end;
	}
	tab[j] = NULL;
	return (tab);
}
