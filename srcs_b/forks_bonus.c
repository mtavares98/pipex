/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:37:11 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/09 20:37:08 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	child_process(int input, int output, t_data *d, char **envp)
{
	d->pid[++d->i] = fork();
	if (d->pid[d->i] == -1)
		exit_prog(d, "Fork wasn't created successfully\n", 1);
	if (d->pid[d->i] == 0)
	{
		if (dup2(input, STDIN_FILENO) == -1)
			exit_prog(d, "Dup2 input wasn't successfull\n", 1);
		close(input);
		if (dup2(output, STDOUT_FILENO) == -1)
			exit_prog(d, "Dup2 output wasn't successfull\n", 1);
		close(output);
		if (execve(d->cp[d->i], d->cmd[d->i], envp) == -1)
			exit_prog(d, "Execve doesn't exec successfully\n", 1);
		exit(0);
	}
	close(input);
	close(output);
}

void	handle_fork(t_data *d, char **envp)
{
	d->i = -1;
	d->j = 0;
	d->k = 0;
	if (pipe(d->pfd[d->j]) == -1)
		exit_prog(d, "Pipe wasn't created successfully\n", 1);
	child_process(d->infile, d->pfd[d->j][1], d, envp);
	d->j++;
	d->k = 0;
	while (d->i < d->nbr_cp - 2)
	{
		if (pipe(d->pfd[d->j]) == -1)
			exit_prog(d, "Pipe wasn't created successfully\n", 1);
		child_process(d->pfd[d->k][0], d->pfd[d->j][1], d, envp);
		if (++d->j > 1)
			d->j = 0;
		if (++d->k > 1)
			d->k = 0;
	}
	child_process(d->pfd[d->k][0], d->outfile, d, envp);
	waitpid(-1, NULL, 0);
}
