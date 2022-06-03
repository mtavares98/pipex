/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:20:30 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/03 14:20:42 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	variables_init(char ***cmd, char **pc, int *pid, t_data *d)
{
	int	i;

	i = -1;
	if (cmd)
		while (++i < d->nbr_pc)
			cmd[i] = NULL;
	i = -1;
	if (pc)
		while (++i < d->nbr_pc)
			pc[i] = NULL;
	if (pid)
		while (++i < d->nbr_pc)
			pid[i] = 0;
}
