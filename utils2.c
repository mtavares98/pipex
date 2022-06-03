/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:50:59 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/03 14:20:27 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_fork(t_data *d, char **envp)
{
	if (d->i < d->nbr_pc - 1)
		if (pipe(d->pfd[d->j]) == -1)
			exit_prog(d, "Error with pipe\n", 1);
	d->pid[d->i] = fork();
	if (d->pid[d->i] == -1)
		exit_prog(d, "Fork failed\n", 1);
	else if (d->pid[d->i] == 0)
		decide_process(d, envp);
	if (d->i % 2 == 0)
	{
		if (d->pfd[d->k][0] != -1)
			close(d->pfd[d->k][0]);
		close(d->pfd[d->j][1]);
	}
	else
	{
		if (d->pfd[d->j][1] != -1)
			close(d->pfd[d->j][1]);
		close(d->pfd[d->k][0]);
	}
}

void	exit_prog(t_data *d, char *s, int i)
{
	if (i == 1)
		ft_printf("%s", s);
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
	if (d->pid)
		free(d->pid);
	exit(i);
}

void	preparation(int ac, char **av, char **env, t_data *d)
{
	d->nbr_pc = ac - 3;
	d->pfd[1][0] = -1;
	d->pfd[1][1] = -1;
	d->cmd = malloc(sizeof(char **) * (d->nbr_pc + 1));
	if (!d->cmd)
		exit_prog(d, "Memory allocation failed for cmd\n", 1);
	d->pc = malloc(sizeof(char *) * (d->nbr_pc + 1));
	variables_init(d->cmd, NULL, NULL, d);
	if (!d->pc)
		exit_prog(d, "Memory allocation failed for pc\n", 1);
	variables_init(NULL, d->pc, NULL, d);
	d->pid = malloc(sizeof(int) * d->nbr_pc);
	if (!d->pid)
		exit_prog(d, "Memory allocation failed for pid\n", 1);
	variables_init(NULL, NULL, d->pid, d);
	parse_args(av, d, env);
	d->infile = open(av[1], O_RDONLY);
	if (d->infile < 0)
		exit_prog(d, "File doesn't exits\n", 1);
	d->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (d->infile < 0)
		exit_prog(d, "File doesn't exits\n", 1);
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
			exit_prog(d, "Invalid argument\n", 1);
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
				exit_prog(d, "Path to binary not found\n", 1);
			free(d->pc[d->i]);
		}
	}
	d->pc[d->i] = NULL;
}
