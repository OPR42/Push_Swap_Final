/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:38:37 by orobert           #+#    #+#             */
/*   Updated: 2025/12/23 10:38:39 by orobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ps_utf8_encode(uint32_t cp, unsigned char out[4])
{
	if (cp > 0x10FFFF)
		return (0);
	if (cp >= 0xD800 && cp <= 0xDFFF)
		return (0);
	if (cp <= 0x7F)
		return (out[0] = (unsigned char)cp, 1);
	if (cp <= 0x7FF)
	{
		out[0] = (unsigned char)(0xC0 | (cp >> 6));
		out[1] = (unsigned char)(0x80 | (cp & 0x3F));
		return (2);
	}
	if (cp <= 0xFFFF)
	{
		out[0] = (unsigned char)(0xE0 | (cp >> 12));
		out[1] = (unsigned char)(0x80 | ((cp >> 6) & 0x3F));
		out[2] = (unsigned char)(0x80 | (cp & 0x3F));
		return (3);
	}
	out[0] = (unsigned char)(0xF0 | (cp >> 18));
	out[1] = (unsigned char)(0x80 | ((cp >> 12) & 0x3F));
	out[2] = (unsigned char)(0x80 | ((cp >> 6) & 0x3F));
	out[3] = (unsigned char)(0x80 | (cp & 0x3F));
	return (4);
}

uint32_t	ps_utf8_next(const char **s, uint32_t cp)
{
	const unsigned char	*p = (const unsigned char *)*s;

	if (*p < 0x80)
		return ((*s)++, (uint32_t)(*p));
	if ((*p & 0xE0) == 0xC0)
	{
		cp = ((p[0] & 0x1F) << 6) | (p[1] & 0x3F);
		*s += 2;
		return (cp);
	}
	if ((*p & 0xF0) == 0xE0)
	{
		cp = ((p[0] & 0x0F) << 12) | ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
		*s += 3;
		return (cp);
	}
	if ((*p & 0xF8) == 0xF0)
	{
		cp = ((p[0] & 0x07) << 18) | ((p[1] & 0x3F) << 12)
			| ((p[2] & 0x3F) << 6) | (p[3] & 0x3F);
		*s += 4;
		return (cp);
	}
	(*s)++;
	return ((uint32_t) '?');
}

int	ps_utf8_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		(void)ps_utf8_next(&s, 0);
		len++;
	}
	return (len);
}

void	ps_write_unicode(int fd, uint32_t cp)
{
	unsigned char	u8[4];
	int				n;

	n = ps_utf8_encode(cp, u8);
	if (n == 0)
		return ;
	write(fd, u8, n);
}

void	ps_forward_utf8_string(const char **s, unsigned int steps)
{
	unsigned int	i;

	i = 0;
	while (i < steps)
	{
		ps_utf8_next(s, 0);
		i++;
	}
}
