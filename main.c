/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:16:06 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/02 17:05:33 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	process_final(t_data *d, char **env)
{
	if (dup2(d->outfile, STDOUT_FILENO) == -1)
		return ;
	close(d->infile);
	close(d->pfd[1]);
	close(d->outfile);
	if (dup2(d->pfd[0], STDIN_FILENO) == -1)
		return ;
	close(d->pfd[0]);
	if (execve(d->pc[d->i], d->cmd[d->i], env) == -1)
		perror("Error child2\n");
}

static void	process_middle(t_data *d, char **env)
{
	if (dup2(d->pfd[1], STDOUT_FILENO) == -1)
		return ;
	close(d->infile);
	close(d->outfile);
	close(d->pfd[1]);
	if (dup2(d->pfd[0], STDIN_FILENO) == -1)
		return ;
	close(d->pfd[0]);
	if (execve(d->pc[d->i], d->cmd[d->i], env) == -1)
		perror("Error child2\n");
}

static void	process_initial(t_data *d, char **env)
{
	if (dup2(d->pfd[1], STDOUT_FILENO) == -1)
		return ;
	close(d->pfd[0]);
	close(d->pfd[1]);
	close(d->outfile);
	if (dup2(d->infile, STDIN_FILENO) == -1)
		return ;
	close(d->infile);
	if (execve(d->pc[d->i], d->cmd[d->i], env) == -1)
		perror("Error child1\n");
}

static void	decide_process(t_data *d, char **env)
{
	if (!d->i)
		process_initial(d, env);
	else if (d->i == d->nbr_pc - 1)
		process_final(d, env);
	else
		process_middle(d, env);
}

int	main(int ac, char **av, char **envp)
{
	t_data	d;

	d.cmd = NULL;
	d.pc = NULL;
	if (ac < 5)
		exit_prog(&d, "Invalid numbers of arguments\n", 1);
	preparation(ac, av, envp, &d);
	d.i = -1;
	while (++d.i < d.nbr_pc)
	{
		if (d.i % 2 == 0)
			if (pipe(d.pfd) == -1)
				exit_prog(&d, "Error with pipe\n", 1);
		d.pid = fork();
		if (d.pid == -1)
			exit_prog(&d, "Fork failed\n", 1);
		else if (d.pid == 0)
			decide_process(&d, envp);
		if (d.i % 2 == 0)
			close(d.pfd[1]);
		else
			close(d.pfd[0]);
	}
	wait(NULL);
	close(d.infile);
	close(d.outfile);
	exit_prog(&d, 0);
}
