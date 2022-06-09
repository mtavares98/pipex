/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:42:19 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/09 15:48:08 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exit_prog(t_data *d, char *s, int i)
{
	if (i != 0)
		printf_fd(2, "Error\n%s", s);
	if (d->cmd)
	{
		d->i = -1;
		while (d->cmd[++d->i])
		{
			d->j = -1;
			while (d->cmd[d->i][++d->j])
				free(d->cmd[d->i][d->j]);
			free(d->cmd[d->i]);
		}
		free(d->cmd);
	}
	if (d->cp)
	{
		d->i = -1;
		while (d->cp[++d->i])
			free(d->cp[d->i]);
		free(d->cp);
	}
	if (d->pid)
		free(d->pid);
	exit(i);
}
