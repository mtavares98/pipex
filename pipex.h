/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:27:41 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/07 17:09:11 by mtavares         ###   ########.fr       */
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

// # define malloc(x) NULL

typedef struct s_data
{
	char	***cmd;
	char	**cp;
	int		nbr_cp;
	int		pid;
	int		i;
	int		j;
	int		k;
	int		infile;
	int		outfile;
	int		pfd[2];
}	t_data;

void	initial_set(int ac, char **av, t_data *d);
void	exit_prog(t_data *d, char *s, int i);
int		strncmp(const char *s1, const char *s2, size_t n);
char	**split(const char *s, char c);
void	parse_args(char **av, t_data *d, char *path);
char	*get_complete_path(char *cmd, char **path);
char	*get_path(char **envp);
#endif
