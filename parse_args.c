/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:21:45 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/07 18:42:59 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	variable_init(char cmd, char cp, t_data *d)
{
	int	i;

	i = -1;
	if (cmd)
		while (++i <= d->nbr_cp)
			d->cmd[i] = NULL;
	i = -1;
	if (cp)
		while (++i <= d->nbr_cp)
			d->cp[i] = NULL;
}

void	initial_set(int ac, char **av, t_data *d)
{
	if (ac != 5)
		exit(ft_printf("Error\nWrong numbers of arguments\n", 1));
	d->cmd = NULL;
	d->cp = NULL;
	d->nbr_cp = ac - 3;
	d->infile = open(av[1], O_RDONLY);
	if (d->infile == -1)
		exit(ft_printf("Error\nFailed open infile\n"));
	d->outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (d->outfile == -1)
		exit(ft_printf("Error\nOn open the outfile\n"));
	d->cmd = malloc(sizeof(char **) * (d->nbr_cp + 1));
	if (!d->cmd)
		exit(ft_printf("Error\nAllocation for cmd failed\n"));
	variable_init(1, 0, d);
	d->cp = malloc(sizeof(char *) * (d->nbr_cp + 1));
	if (!d->cp)
		exit_prog(d, "Allocation for pc failed\n", 1);
	variable_init(0, 1, d);
}

char	*get_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
	return (NULL);
}

void	parse_args(char **av, t_data *d, char *path)
{
	char	*p;

	d->i = -1;
	while (++d->i < d->nbr_cp)
	{
		d->cmd[d->i] = split(av[2 + d->i], ' ');
		if (!d->cmd[d->i][0])
			exit_prog(d, "Invalid argument\n", 1);
	}
	d->i = -1;
	while (++d->i < d->nbr_cp)
	{
		p = path;
		while (1)
		{
			d->cp[d->i] = get_complete_path(d->cmd[d->i][0], &p);
			if (access(d->cp[d->i], F_OK) != -1)
				break ;
			if (!*p)
				exit_prog(d, "Path to binary not found\n", 1);
			free(d->cp[d->i]);
		}
	}
	d->cp[d->i] = NULL;
}
