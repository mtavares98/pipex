/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:17:22 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/07 01:04:12 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h> 
# include "printf/ft_printf.h"
# include "gnl/get_next_line.h"

// # define malloc(x) NULL

typedef struct s_data
{
	char	***cmd;
	char	**cp;
	char	*hdt;
	int		nbr_cp;
	int		i;
	int		j;
	int		k;
	int		heredoc;
	int		infile;
	int		outfile;
	int		pid;
	int		pfd[2][2];
}	t_data;

void	heredoc(t_data *d, char **av, int ac);
void	exit_prog(t_data *d, char *s, int i);
int		strncmp(const char *s1, const char *s2, size_t n);
char	**split(const char *s, char c);
void	parse_args(char **av, t_data *d, char *path);
char	*get_complete_path(char *cmd, char **path);
char	*get_path(char **envp);

#endif