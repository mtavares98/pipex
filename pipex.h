/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:27:41 by mtavares          #+#    #+#             */
/*   Updated: 2022/05/27 12:40:08 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h> 
# include "ft_printf.h"

typedef struct s_data
{
	char	**cmd;
	char	*pc;
}	t_data;

void	parse_args(char **av, t_data *d, char **envp);
char	**split(const char *s, char c);
int		strncmp(const char *s1, const char *s2, size_t n);
char	*strjoin(char *cmd, char **path);

#endif
