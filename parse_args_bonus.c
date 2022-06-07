/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:21:45 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/07 16:16:36 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static size_t	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

static void	read_heredoc(t_data *d, char **av)
{
	char	*s;

	s = NULL;
	while (strncmp(av[2], s, ft_strlen(av[2])))
	{
		if (s)
			free(s);
		s = get_next_line(0);
		write(d->infile, s, ft_strlen(s));
	}
	if (s)
		free(s);
}

void	heredoc(t_data *d, char **av, int ac)
{
	d->heredoc = 0;
	if (strncmp(av[1], "heredoc", 8))
	{
		if (ac < 5)
			exit_prog(d, "Wrong numbers of arguments\n", 1);
		d->infile = open(av[1], O_RDONLY);
		if (d->infile == -1)
			exit_prog(d, "Failed open infile\n", 1);
		d->outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (d->outfile == -1)
			exit_prog(d, "On open the outfile\n", 1);
		return ;
	}
	if (ac < 6)
		exit_prog(d, "Wrong numbers of arguments\n", 1);
	d->heredoc = 1;
	d->hdt = "heredoc.txt";
	d->infile = open(d->hdt, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (d->infile == -1)
		exit_prog(d, "Failed open tmpfile\n", 1);
	d->outfile = open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (d->outfile == -1)
		exit_prog(d, "On open the outfile\n", 1);
	read_heredoc(d, av);
	close(d->infile);
}

char	*get_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
	return (NULL);
}

void	parse_args(char **av, t_data *d, char *path)
{
	char	*p;

	d->i = -1;
	while (++d->i < d->nbr_cp)
	{
		d->cmd[d->i] = split(av[2 + d->heredoc + d->i], ' ');
		if (!d->cmd[d->i][0])
			exit_prog(d, "Invalid argument\n", 1);
	}
	d->cmd[d->i] = NULL;
	d->i = -1;
	while (++d->i < d->nbr_cp)
	{
		p = path;
		while (1)
		{
			d->cp[d->i] = get_complete_path(d->cmd[d->i][0], &p);
			if (access(d->cp[d->i], F_OK) != -1)
				break ;
			if (!*p)
				exit_prog(d, "Path to binary not found\n", 1);
			free(d->cp[d->i]);
		}
	}
	d->cp[d->i] = NULL;
}
