/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:27:41 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/03 14:21:31 by mtavares         ###   ########.fr       */
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
	char	**pc;
	int		nbr_pc;
	int		*pid;
	int		i;
	int		j;
	int		k;
	int		infile;
	int		outfile;
	int		pfd[2][2];
}	t_data;

void	variables_init(char ***cmd, char **pc, int *pid, t_data *d);
void	parse_args(char **av, t_data *d, char **envp);
char	**split(const char *s, char c);
int		strncmp(const char *s1, const char *s2, size_t n);
char	*get_complete_path(char *cmd, char **path);
void	preparation(int ac, char **av, char **env, t_data *d);
void	exit_prog(t_data *d, char *s, int i);
void	process_final(t_data *d, char **env);
void	process_middle(t_data *d, char **env);
void	process_initial(t_data *d, char **env);
void	decide_process(t_data *d, char **env);
void	handle_fork(t_data *d, char **envp);

#endif
