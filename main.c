/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:16:06 by mtavares          #+#    #+#             */
/*   Updated: 2022/05/30 13:38:52 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_final(int ac, char **av, t_data *d, char **env)
{
	int	fd[2];

	fd[0] = open(av[1], O_TRUNC | O_CREAT | O_RDONLY, 0);
	if (fd[0] == -1)
		exit(ft_printf("Invalid file\n"));
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		exit(ft_printf("Was an error on dup2\n"));
	}
	close(fd[0]);
	fd[1] = open(av[ac - 1], O_TRUNC | O_RDONLY);
	if (fd[1] == -1)
		exit(ft_printf("Invalid file\n"));
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		exit(ft_printf("Was an error on dup2\n"));
	}
	close(fd[1]);
	if (execve(d->pc[d->nbr_pc], &d->cmd[d->nbr_pc -1][1], env) == -1)
		exit(ft_printf("Has been an error with execve\n"));
	exit(0);
}

void	process_child(char **av, t_data *d, char **env)
{
	int	fd;

	fd = open(av[1], O_TRUNC | O_WRONLY);
	if (fd == -1)
		exit(ft_printf("Invalid file\n"));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		exit(ft_printf("Was an error on dup2\n"));
	}
	close(fd);
	if (execve(d->pc[0], &d->cmd[0][1], env) == -1)
		exit(ft_printf("Has been an error with execve\n"));
	exit(0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	d;
	int		id;

	d.nbr_pc = ac - 3;
	d.cmd = malloc(sizeof(char **) * (d.nbr_pc + 1));
	d.pc = malloc(sizeof(char *) * (d.nbr_pc + 1));
	if (ac != 5)
		exit(ft_printf("Invalid numbers of arguments\n") != 0);
	parse_args(av, &d, envp);
	id = fork();
	if (id == -1)
		exit(ft_printf("Error ocurred while forking\n") != 0);
	if (id == 0)
		process_child(av, &d, envp);
	else
		wait(NULL);
	id = fork();
	if (id == -1)
		exit(ft_printf("Error ocurred while forking\n") != 0);
	if (id == 0)
		process_final(ac, av, &d, envp);
	else
		wait(NULL);
}
