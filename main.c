/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:16:06 by mtavares          #+#    #+#             */
/*   Updated: 2022/05/31 19:07:56 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	preparation(int ac, char **av, char **env, t_data *d)
{
	parse_args(av, d, env);
	d->infile = open(av[1], O_RDONLY);
	if (d->infile < 0)
		exit(ft_printf("File doesn't exits\n"));
	d->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (d->infile < 0)
		exit(ft_printf("File doesn't exits\n"));
	if (pipe(d->pfd) == -1)
		exit(ft_printf("Error with pipe\n"));
}

void	process_final(t_data *d, char **env)
{
	close(d->pfd[1]);
	if (dup2(d->pfd[0], STDIN_FILENO) == -1)
	{
		close(d->pfd[0]);
		perror("Error child1\n");
		exit(2);
	}
	close(d->pfd[0]);
	if (dup2(d->outfile, STDIN_FILENO) == -1)
	{
		close(d->outfile);
		perror("Error child1\n");
		exit(2);
	}
	close(d->outfile);
	if (execve(d->pc[1], d->cmd[1], env) == -1)
	{
		perror("Error child2\n");
		exit(6);
	}
	exit(0);
}

void	process_child(t_data *d, char **env)
{
	close(d->pfd[0]);
	if (dup2(d->pfd[1], STDOUT_FILENO) == -1)
	{
		close(d->pfd[1]);
		perror("Error child1\n");
		exit(2);
	}
	close(d->pfd[1]);
	if (dup2(d->infile, STDIN_FILENO) == -1)
	{
		close(d->infile);
		perror("Error child1\n");
		exit(2);
	}
	close(d->infile);
	if (execve(d->pc[0], d->cmd[0], env) == -1)
	{
		perror("Error child1\n");
		exit(6);
	}
	exit(0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	d;

	d.nbr_pc = ac - 3;
	if (ac != 5)
		exit(ft_printf("Invalid numbers of arguments\n") != 0);
	preparation(ac, av, envp, &d);
	d.id = fork();
	if (d.id == -1)
		exit(ft_printf("Error ocurred while forking\n") != 0);
	if (d.id != 0)
		wait(NULL);
	else
		process_child(&d, envp);
	d.id = fork();
	if (d.id == -1)
		exit(ft_printf("Error ocurred while forking\n") != 0);
	if (d.id != 0)
		wait(NULL);
	else
		process_final(&d, envp);
}
