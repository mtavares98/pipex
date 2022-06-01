/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:16:06 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/01 22:55:06 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	process_final(t_data *d, char **env)
{
	if (dup2(d->outfile, STDOUT_FILENO) == -1)
		return ;
	close(d->pfd[1]);
	close(d->outfile);
	if (dup2(d->pfd[0], STDIN_FILENO) == -1)
		return ;
	close(d->pfd[0]);
	if (execve(d->pc[1], d->cmd[1], env) == -1)
		perror("Error child2\n");
}

static void	process_child(t_data *d, char **env)
{
	if (dup2(d->pfd[1], STDOUT_FILENO) == -1)
		return ;
	close(d->pfd[0]);
	close(d->pfd[1]);
	if (dup2(d->infile, STDIN_FILENO) == -1)
		return ;
	close(d->infile);
	if (execve(d->pc[0], d->cmd[0], env) == -1)
		perror("Error child1\n");
}

int	main(int ac, char **av, char **envp)
{
	t_data	d;

	if (ac != 5)
		exit_error(&d, "Invalid numbers of arguments\n");
	preparation(ac, av, envp, &d);
	d.pid[0] = fork();
	if (d.pid[0] == -1)
		exit_error(&d, "Fork failed\n");
	if (d.pid[0] == 0)
		process_child(&d, envp);
	close(d.infile);
	d.pid[d.nbr_pc -1] = fork();
	if (d.pid[d.nbr_pc -1] == -1)
		exit_error(&d, "Fork failed\n");
	if (d.pid[d.nbr_pc -1] == 0)
		process_final(&d, envp);
	close(d.pfd[0]);
	close(d.pfd[1]);
	waitpid(d.pid[d.nbr_pc -1], NULL, 0);
	waitpid(d.pid[d.nbr_pc -1], NULL, 0);
	exit_prog(&d, 0);
}
