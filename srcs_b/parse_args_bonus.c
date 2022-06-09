/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:36:38 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/09 20:01:13 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
		d->cmd[d->i] = split(av[2 + d->heredoc + d->i], ' ');
		if (!d->cmd[d->i][0])
			exit_prog(d, "Invalid argument\n", 1);
	}
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
				exit_prog(d, "Command not found\n", 1);
			free(d->cp[d->i]);
		}
	}
}
