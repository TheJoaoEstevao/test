/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:50:34 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 17:50:35 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

static int	ft_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_in_set(s1[end - 1], set))
		end--;
	str = ft_substr(s1, start, end - start);
	return (str);
}

char	*ft_strtok(char *str, char *delimiter)
{
	static char	*next_token = NULL;
	char		*token;

	if (str != NULL)
		next_token = str;
	if (next_token == NULL || *next_token == '\0')
		return (NULL);
	while (*next_token != '\0' && ft_strchr(delimiter, *next_token) != NULL)
		next_token++;
	if (*next_token == '\0')
		return (NULL);
	token = next_token;
	while (*next_token != '\0' && ft_strchr(delimiter, *next_token) == NULL)
		next_token++;
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	return (token);
}
