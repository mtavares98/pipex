/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:16:06 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/05 16:12:13 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_final(t_data *d, char **env)
{
	if (dup2(d->outfile, STDOUT_FILENO) == -1)
		return ;
	close(d->infile);
	close(d->pfd[d->k][1]);
	close(d->outfile);
	if (dup2(d->pfd[d->k][0], STDIN_FILENO) == -1)
		return ;
	close(d->pfd[d->k][0]);
	if (execve(d->pc[d->i], d->cmd[d->i], env) == -1)
		perror("Error child2\n");
	exit(0);
}

void	process_middle(t_data *d, char **env)
{
	close(d->pfd[d->j][0]);
	if (dup2(d->pfd[d->j][1], STDOUT_FILENO) == -1)
		return ;
	close(d->pfd[d->j][1]);
	close(d->infile);
	close(d->outfile);
	if (dup2(d->pfd[d->k][0], STDIN_FILENO) == -1)
		return ;
	close(d->pfd[d->k][0]);
	if (execve(d->pc[d->i], d->cmd[d->i], env) == -1)
		exit_prog(d, "Error with fork\n", 1);
	exit(0);
}

void	process_initial(t_data *d, char **env)
{
	close(d->pfd[d->j][0]);
	if (dup2(d->pfd[d->j][1], STDOUT_FILENO) == -1)
		return ;
	close(d->pfd[d->j][1]);
	close(d->outfile);
	if (dup2(d->infile, STDIN_FILENO) == -1)
		return ;
	close(d->infile);
	if (execve(d->pc[d->i], d->cmd[d->i], env) == -1)
		perror("Error child1\n");
	exit(0);
}

void	decide_process(t_data *d, char **env)
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
	d.pid = NULL;
	if (ac < 5)
		exit_prog(&d, "Invalid numbers of arguments\n", 1);
	preparation(ac, av, envp, &d);
	d.i = -1;
	d.j = 0;
	d.k = 1;
	while (++d.i < d.nbr_pc)
	{
		handle_fork(&d, envp);
		if (++d.j > 1)
			d.j = 0;
		if (++d.k > 1)
			d.k = 0;
	}
	while (++d.i < d.nbr_pc)
		waitpid(d.pid[d.i], NULL, 0);
	close(d.infile);
	close(d.outfile);
	exit_prog(&d, NULL, 0);
}
