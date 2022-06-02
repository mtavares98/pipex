/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:50:59 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/02 01:34:11 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(t_data *d, char *s)
{
	ft_printf("Error\n%s", s);
	exit_prog(d, 1);
}

void	exit_prog(t_data *d, int i)
{
	if (d->pc)
	{
		d->i = -1;
		while (d->pc[++d->i])
			free(d->pc[d->i]);
		free(d->pc);
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

void	preparation(int ac, char **av, char **env, t_data *d)
{
	d->nbr_pc = ac - 3;
	d->cmd = malloc(sizeof(char **) * (d->nbr_pc + 1));
	d->pc = malloc(sizeof(char *) * (d->nbr_pc + 1));
	if (!d->cmd || !d->pc)
		exit_error(d, "Memory allocation failed for cmd or pc\n");
	parse_args(av, d, env);
	d->infile = open(av[1], O_RDONLY);
	if (d->infile < 0)
		exit_error(d, "File doesn't exits\n");
	d->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (d->infile < 0)
		exit_error(d, "File doesn't exits\n");
	if (pipe(d->pfd) == -1)
		exit_error(d, "Error with pipe\n");
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

void	parse_args(char **av, t_data *d, char **envp)
{
	char	*p;

	d->i = -1;
	while (++d->i < d->nbr_pc)
	{
		d->cmd[d->i] = split(av[2 + d->i], ' ');
		if (!d->cmd[d->i][0])
			exit_error(d, "Invalid argument\n");
	}
	d->cmd[d->i] = NULL;
	d->i = -1;
	while (++d->i < d->nbr_pc)
	{
		p = get_path(envp);
		while (1)
		{
			d->pc[d->i] = get_complete_path(d->cmd[d->i][0], &p);
			if (access(d->pc[d->i], F_OK) != -1)
				break ;
			if (!*p)
				exit_error(d, "Path to binary not found\n");
			free(d->pc[d->i]);
		}
	}
	d->pc[d->i] = NULL;
}
