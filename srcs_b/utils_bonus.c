/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:33:09 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/09 19:58:24 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = -1 + (s == NULL);
	while (s && s[++i] && s[i] != ':')
		;
	return (i + (s[i] == ':'));
}

static char	**new_str(char **str, const char *s, char c, int counter)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	while (*s == c)
		s++;
	while (s[++i] != c && s[i])
		;
	if (!tmp && i > 0)
		tmp = (char *)malloc(i + 1);
	if (tmp)
	{
		str = new_str(str, s + i, c, counter + 1);
		tmp[i] = '\0';
		while (--i > -1)
			tmp[i] = s[i];
	}
	if (!str)
		str = (char **) malloc(sizeof(char *) * (counter + 1));
	if (!str)
		return (NULL);
	str[counter] = tmp;
	return (str);
}

char	**split(const char *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = new_str(NULL, s, c, 0);
	return (str);
}

int	strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!str1 || !str2)
		return (-1);
	i = -1;
	while (str1[++i] && str2[i] && i < n)
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	if (i < n)
		return (str1[i] - str2[i]);
	return (0);
}

char	*get_complete_path(char *cmd, char **path)
{
	int		i;
	int		j;
	int		path_size;
	char	*np;

	path_size = ft_strlen(*path);
	np = malloc((ft_strlen(cmd) + path_size + 1) * sizeof(char));
	if (!np)
		return (NULL);
	i = -1 * (path != NULL);
	while (path && *path && ++i < path_size - 1)
	{
		np[i] = **path;
		*path += 1;
	}
	if (*path && (**path == ':' || **path != '\0'))
	{
		np[i++] = '/';
		*path += 1;
	}
	j = 0;
	while (cmd && cmd[j])
		np[i++] = cmd[j++];
	np[i] = '\0';
	return (np);
}

/* int	main(void)
{
	int		i;
	char	**str;
	str = split("  tripouille  42  ", ' ');
	i = 0;
	while (str && str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	if (str)
	{
		printf("%s\n", str[i]);
		while (--i < -1)
			free(str[i]);
		free(str);
	}
} */