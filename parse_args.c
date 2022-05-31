/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:50:59 by mtavares          #+#    #+#             */
/*   Updated: 2022/05/31 14:58:28 by mtavares         ###   ########.fr       */
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

	d->cmd = malloc(sizeof(char **) * (d->nbr_pc + 1));
	d->pc = malloc(sizeof(char *) * (d->nbr_pc + 1));
	d->i = -1;
	while (++d->i < d->nbr_pc)
		d->cmd[d->i] = split(av[2 + d->i], ' ');
	d->cmd[d->i] = NULL;
	d->i = -1;
	while (++d->i < d->nbr_pc)
	{
		p = get_path(envp);
		if (!p)
			exit(ft_printf("Path to binaries not found\n") != 0);
		p += 5;
		while (1)
		{
			d->pc[d->i] = get_complete_path(d->cmd[d->i][0], &p);
			if (access(d->pc[d->i], F_OK) != -1)
				break ;
			if (!*p)
			{
				perror("Error\n");
				exit(5);
			}
			free(d->pc[d->i]);
		}
	}
	d->pc[d->i] = NULL;
}
