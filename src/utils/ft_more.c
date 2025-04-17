/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro3 <jopedro3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:51:52 by jopedro3          #+#    #+#             */
/*   Updated: 2024/12/02 16:51:53 by jopedro3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

size_t	ft_nl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (i + (s[i] == '\n'));
}

char	*ft_nl_strjoin(char *s1, char *s2)
{
	int		i;
	size_t	j;
	char	*str;

	str = ft_calloc(ft_nl_strlen(s1) + ft_nl_strlen(s2) + 1, 1);
	if (!str)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	if (i == -1)
		i = 0;
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
		if (s2[j - 1] == '\n')
			break ;
	}
	return (str);
}

static size_t	ft_reset_line(char *str)
{
	size_t	nl;
	size_t	i;
	size_t	j;

	nl = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (nl)
			str[j++] = str[i];
		if (str[i] == '\n')
			nl = 1;
		str[i++] = 0;
	}
	return (nl);
}

char	*ft_gnl(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*temp;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		if (fd >= 0)
			ft_bzero(&buffer[fd], BUFFER_SIZE);
		return (NULL);
	}
	line = NULL;
	while (read(fd, &buffer[fd], BUFFER_SIZE > 0))
	{
		temp = line;
		line = ft_nl_strjoin(temp, &buffer[fd]);
		free(temp);
		if (ft_reset_line(&buffer[fd]))
			break ;
	}
	return (line);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}
