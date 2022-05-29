/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:50:59 by mtavares          #+#    #+#             */
/*   Updated: 2022/05/29 22:57:17 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!strncmp(envp[i], "PATH=", 5))
			return (envp[i]);
	return (NULL);
}

void	parse_args(char **av, t_data *d, char **envp)
{
	char	*p;

	d->i = -1;
	while (++d->i < d->nbr_pc)
		d->cmd[d->i] = split(av[2 + d->i], ' ');
	d->i = -1;
	while (++d->i < d->nbr_pc)
	{
		p = get_path(envp);
		if (!p)
			exit(ft_printf("Path to binaries not found\n") != 0);
		p += 5;
		while (1)
		{
			d->pc[d->i] = strjoin(d->cmd[d->i][0], &p);
			if (access(d->pc[0], F_OK) != -1)
				break ;
			if (!*p)
				exit(ft_printf("Command doesn't exist\n") != 0);
		}
	}
}
