/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 01:10:20 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/09 17:21:22 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	char	*path;
	t_data	d;

	d.cmd = NULL;
	d.cp = NULL;
	d.pid = NULL;
	if (ac < 5)
		exit_prog(&d, "Wrong number of arguments\n", 1);
	variables_init(ac, av, &d);
	path = get_path(envp);
	if (!path)
		exit_prog(&d, "Path doesn't exist\n", 1);
	parse_args(av, &d, path);
	handle_fork(&d, envp);
	exit_prog(&d, NULL, 0);
}
