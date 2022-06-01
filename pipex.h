/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:27:41 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/01 15:37:39 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h> 
# include "printf/ft_printf.h"

typedef struct s_data
{
	char	***cmd;
	char	**pc;
	int		nbr_pc;
	int		pid2;
	int		i;
	int		j;
	int		infile;
	int		outfile;
	int		pfd[2];
	int		pid1;
}	t_data;

void	parse_args(char **av, t_data *d, char **envp);
char	**split(const char *s, char c);
int		strncmp(const char *s1, const char *s2, size_t n);
char	*get_complete_path(char *cmd, char **path);

#endif
