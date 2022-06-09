/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:36:45 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/09 20:27:47 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	variables_init(int ac, t_data *d)
{
	d->nbr_cp = ac - 3 - d->heredoc;
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
