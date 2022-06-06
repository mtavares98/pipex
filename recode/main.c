/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:16:31 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/06 16:17:47 by mtavares         ###   ########.fr       */
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

static void	prepare_fork(t_data *d, char **envp)
{
	d->i = 0;
	d->j = 0;
	d->k = 1;
	if (pipe(d->pfd[d->j]) == -1)
		exit_prog(d, "Pipe\n", 1);
	child_process(d, d->infile, d->pfd[d->j][1], envp);
	d->j++;
	if (++d->k > 1)
		d->k = 0;
	while (++d->i < d->nbr_cp - 1)
	{
		if (pipe(d->pfd[d->j]) == -1)
			exit_prog(d, "Pipe\n", 1);
		child_process(d, d->pfd[d->k][0], d->pfd[d->j][1], envp);
		if (++d->j > 1)
			d->j = 0;
		if (++d->k > 1)
			d->k = 0;
	}
	child_process(d, d->pfd[d->k][0], d->outfile, envp);
}

int	main(int ac, char **av, char **envp)
{
	t_data	d;

	if (ac < 5)
		return (ft_printf("Wrong number of arguments\n"));
	d.nbr_cp = ac - 3;
	d.cmd = malloc(sizeof(char **) * (d.nbr_cp + 1));
	if (!d.cmd)
		exit_prog(&d, "Allocation for cmd failed\n", 1);
	variable_init(d.cmd, NULL, &d);
	d.cp = malloc(sizeof(char *) * (d.nbr_cp + 1));
	if (!d.cp)
		exit_prog(&d, "Allocation for cmd failed\n", 1);
	variable_init(NULL, d.cp, &d);
	d.infile = open(av[1], O_RDONLY);
	if (d.infile == -1)
		exit_prog(&d, "On open the infile\n", 1);
	d.outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (d.outfile == -1)
		exit_prog(&d, "On open the outfile\n", 1);
	parse_args(av, &d, get_path(envp));
	prepare_fork(&d, envp);
	exit_prog(&d, NULL, 0);
}
