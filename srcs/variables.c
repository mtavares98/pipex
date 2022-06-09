/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:36:45 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/09 16:53:55 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	variables_init(int ac, char **av, t_data *d)
{
	d->nbr_cp = ac - 3;
	d->infile = open(av[1], O_RDONLY);
	if (d->infile == -1)
		exit_prog(d, "Infile doesn't exist\n", 1);
	d->outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (d->outfile == -1)
		exit_prog(d, "Outfile wasn't created\n", 1);
	d->cmd = malloc(sizeof(char **) * (d->nbr_cp + 1));
	if (!d->cmd)
		exit_prog(d, "Allocation of memory failed on cmd\n", 1);
	d->i = -1;
	while (++d->i <= d->nbr_cp)
		d->cmd[d->i] = NULL;
	d->cp = malloc(sizeof(char *) * (d->nbr_cp + 1));
	if (!d->cp)
		exit_prog(d, "Allocation of memory failed on cp\n", 1);
	d->i = -1;
	while (++d->i <= d->nbr_cp)
		d->cp[d->i] = NULL;
	d->pid = malloc(sizeof(int) * (d->nbr_cp));
	if (!d->pid)
		exit_prog(d, "Allocation of memory failed on pid\n", 1);
	d->i = -1;
	while (++d->i < d->nbr_cp)
		d->pid[d->i] = 0;
}
