/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevao <jestevao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:50:34 by jopedro3          #+#    #+#             */
/*   Updated: 2025/06/03 11:28:03 by jestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_is_str_equal(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == s2[i]);
}

t_bool	ft_is_present(const char *str, char c)
{
	if (!str)
		return (FALSE);
	while (*str)
	{
		if (*str == c)
			return (TRUE);
		str++;
	}
	return (FALSE);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_present(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_is_present(set, s1[end - 1]))
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
	while (*next_token != '\0' && ft_is_present(delimiter, *next_token))
		next_token++;
	if (*next_token == '\0')
		return (NULL);
	token = next_token;
	while (*next_token != '\0' && !ft_is_present(delimiter, *next_token))
		next_token++;
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	return (token);
}
