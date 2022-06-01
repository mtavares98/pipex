/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:16:06 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/01 16:16:42 by mtavares         ###   ########.fr       */
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

void	process_child(t_data *d, char **env)
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

	d.nbr_pc = ac - 3;
	if (ac != 5)
		exit(ft_printf("Invalid numbers of arguments\n") != 0);
	preparation(ac, av, envp, &d);
	d.pid1 = fork();
	if (d.pid1 == -1)
		return (1);
	if (d.pid1 == 0)
		process_child(&d, envp);
	close(d.infile);
	d.pid2 = fork();
	if (d.pid2 == -1)
		return (1);
	if (d.pid2 == 0)
		process_final(&d, envp);
	close(d.pfd[0]);
	close(d.pfd[1]);
	waitpid(d.pid1, NULL, 0);
	waitpid(d.pid2, NULL, 0);
	system("leaks -- pipex");
}
