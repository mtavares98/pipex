/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:16:06 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/07 17:20:22 by mtavares         ###   ########.fr       */
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
	char	*p;
	t_data	d;

	initial_set(ac, av, &d);
	p = get_path(envp);
	if (!p)
		exit_prog(&d, "Path doesn't exist\n", 1);
	parse_args(av, &d, p);
	if (pipe(d.pfd) == -1)
		exit_prog(&d, "Pipe\n", 1);
	d.i = 0;
	child_process(&d, d.infile, d.pfd[1], envp);
	d.i = 1;
	child_process(&d, d.pfd[0], d.outfile, envp);
	exit_prog(&d, NULL, 0);
}
