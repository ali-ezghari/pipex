/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezghari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:32:12 by aezghari          #+#    #+#             */
/*   Updated: 2024/12/28 11:17:00 by aezghari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**mem_error(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i++]);
	}
	free(tab);
	return (NULL);
}

static int	count_words(char const *str, char sep)
{
	int		i;
	int		in_word;
	int		count;

	i = 0;
	in_word = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (!in_word && str[i] != sep)
		{
			in_word = 1;
			count++;
		}
		else if (str[i] == sep)
		{
			in_word = 0;
		}
		i++;
	}
	return (count);
}

static char	*copy(char const *str, int *start, char sep)
{
	char	*dest;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (str[*start] == sep && str[*start])
	{
		(*start)++;
	}
	while (str[*start + len] != sep && str[*start + len])
	{
		len++;
	}
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len && str[*start])
	{
		dest[i++] = str[*start];
		(*start)++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *str, char sep)
{
	int		size;
	int		i;
	int		pos;
	char	**ptr;

	i = 0;
	pos = 0;
	if (!str)
		return (NULL);
	size = count_words(str, sep);
	ptr = malloc(sizeof(char *) * (size + 1));
	if (!ptr)
		return (NULL);
	ptr[size] = NULL;
	while (i < size)
	{
		ptr[i] = copy(str, &pos, sep);
		if (!ptr[i])
			return (mem_error(ptr));
		i++;
	}
	return (ptr);
}
