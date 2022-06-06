/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:21:45 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/06 14:51:46 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_prog(t_data *d, char *s, int i)
{
	if (i != 0)
		ft_printf("Error\n%s", s);
	if (d->cp)
	{
		d->i = -1;
		while (d->cp[++d->i])
			free(d->cp[d->i]);
		free(d->cp);
	}
	if (d->cmd)
	{
		d->i = -1;
		while (d->cmd[++d->i])
		{
			d->j = -1;
			while (d->cmd[d->i][++d->j])
				free(d->cmd[d->i][d->j]);
			free(d->cmd[d->i]);
		}
		free(d->cmd);
	}
	exit(i);
}

char	*get_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
	return (NULL);
}

void	parse_args(char **av, t_data *d, char *path)
{
	char	*p;

	d->i = -1;
	while (++d->i < d->nbr_cp)
	{
		d->cmd[d->i] = split(av[2 + d->i], ' ');
		if (!d->cmd[d->i][0])
			exit_prog(d, "Invalid argument\n", 1);
	}
	d->cmd[d->i] = NULL;
	d->i = -1;
	while (++d->i < d->nbr_cp)
	{
		p = path;
		while (1)
		{
			d->cp[d->i] = get_complete_path(d->cmd[d->i][0], &p);
			if (access(d->cp[d->i], F_OK) != -1)
				break ;
			if (!*p)
				exit_prog(d, "Path to binary not found\n", 1);
			free(d->cp[d->i]);
		}
	}
	d->cp[d->i] = NULL;
}
