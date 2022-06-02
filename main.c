/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:16:06 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/02 16:56:45 by mtavares         ###   ########.fr       */
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
	{
		ft_printf("decided initial process\n");
		process_initial(d, env);
	}
	else if (d->i == d->nbr_pc - 1)
	{
		ft_printf("decided final process\n");
		process_final(d, env);
	}
	else
	{
		ft_printf("decided middle process\n");
		process_middle(d, env);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	d;

	d.cmd = NULL;
	d.pc = NULL;
	if (ac < 5)
		exit_error(&d, "Invalid numbers of arguments\n");
	preparation(ac, av, envp, &d);
	d.i = -1;
	while (++d.i < d.nbr_pc)
	{
		if (d.i % 2 == 0)
			if (pipe(d.pfd) == -1)
				exit_error(&d, "Error with pipe\n");
		d.pid = fork();
		if (d.pid == -1)
			exit_error(&d, "Fork failed\n");
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
