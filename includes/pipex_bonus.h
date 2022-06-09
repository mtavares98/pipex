/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 01:08:46 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/09 20:27:57 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h> 
# include "../libs/printf_fd/include/printf_fd.h"
# include "get_next_line.h"

// # define malloc(x) NULL

typedef struct s_data
{
	char	***cmd;
	char	**cp;
	char	*hdt;
	int		*pid;
	int		pfd[2][2];
	int		nbr_cp;
	int		i;
	int		j;
	int		k;
	int		heredoc;
	int		infile;
	int		outfile;
}	t_data;

void	exit_prog(t_data *d, char *s, int i);
void	heredoc(t_data *d, int ac, char **av);
void	variables_init(int ac, t_data *d);
char	*get_complete_path(char *cmd, char **path);
char	*get_path(char **envp);
void	parse_args(char **av, t_data *d, char *path);
char	**split(const char *s, char c);
int		strncmp(const char *s1, const char *s2, size_t n);
void	handle_fork(t_data *d, char **envp);

#endif