/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:16:06 by mtavares          #+#    #+#             */
/*   Updated: 2022/05/29 14:05:42 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_child(char **av, t_data *d, char **env)
{
	int	fd;

	fd = open(av[1], O_TRUNC | O_CREAT | O_RDWR);
	if (fd == -1)
		exit(ft_printf("Invalid file\n") != 0);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		exit(ft_printf("Was an error on dup2\n"));
	}
	close(fd);
	if (execve(d->pc[0], &d->cmd[0][0], env) == -1)
		exit(ft_printf("Has been an error with execve\n") != 0);
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
}
