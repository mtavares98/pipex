/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:16:06 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/07 00:24:35 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	variable_init(char ***cmd, char **cp, t_data *d)
{
	int	i;

	i = -1;
	if (cmd)
		while (++i < d->nbr_cp)
			cmd[i] = NULL;
	i = -1;
	if (cp)
		while (++i < d->nbr_cp)
			cp[i] = NULL;
}

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

void	child_process(t_data *d, int input, int output, char **envp)
{
	d->pid = fork();
	if (d->pid == -1)
		exit_prog(d, "Fork\n", 1);
	if (!d->pid)
	{
		if (dup2(input, STDIN_FILENO) == -1 && close(input))
			exit_prog(d, "Dup of stdin failed\n", 1);
		if (dup2(output, STDOUT_FILENO) == -1 && close(output))
			exit_prog(d, "Dup to stdout failed\n", 1);
		if (execve(d->cp[d->i], d->cmd[d->i], envp) == -1)
			perror("Execve\n");
		exit(0);
	}
	wait(NULL);
	close(input);
	close(output);
}

int	main(int ac, char **av, char **envp)
{
	t_data	d;

	if (ac != 5)
		exit_prog(&d, "Wrong numbers of arguments\n", 1);
	d.infile = open(av[1], O_RDONLY);
	if (d.infile == -1)
		exit_prog(&d, "Failed open infile\n", 1);
	d.outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (d.outfile == -1)
		exit_prog(&d, "On open the outfile\n", 1);
	d.cmd = malloc(sizeof(char **) * (d.nbr_cp + 1));
	if (!d.cmd)
		exit_prog(&d, "Allocation for cmd failed\n", 1);
	variable_init(d.cmd, NULL, &d);
	d.cp = malloc(sizeof(char *) * (d.nbr_cp + 1));
	if (!d.cp)
		exit_prog(&d, "Allocation for cmd failed\n", 1);
	variable_init(NULL, d.cp, &d);
	parse_args(av, &d, get_path(envp));
	if (pipe(d.pfd) == -1)
		exit_prog(&d, "Pipe\n", 1);
	d.i = 0;
	child_process(&d, d.infile, d.pfd[1], envp);
	d.i = 1;
	child_process(&d, d.pfd[0], d.outfile, envp);
	exit_prog(&d, NULL, 0);
}
