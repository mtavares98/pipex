/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 01:01:49 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/09 14:59:16 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h> 
# include "../libs/printf_fd/include/printf_fd.h"

// # define malloc(x) NULL

typedef struct s_data
{
	char	***cmd;
	char	**cp;
	int		*pid;
	int		nbr_cp;
	int		i;
	int		j;
	int		k;
	int		infile;
	int		outfile;
	int		pfd[2];
}	t_data;

void	exit_prog(t_data *d, char *s, int i);
void	variables_init(int ac, char **av, t_data *d);
char	*get_complete_path(char *cmd, char **path);
char	*get_path(char **envp);
void	parse_args(char **av, t_data *d, char *path);
char	**split(const char *s, char c);
int		strncmp(const char *s1, const char *s2, size_t n);
void	handle_fork(t_data *d, char **envp);

#endif