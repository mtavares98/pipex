/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtavares <mtavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:56:11 by mtavares          #+#    #+#             */
/*   Updated: 2022/06/09 20:53:27 by mtavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static size_t	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (1);
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
		printf_fd(d->infile, s);
	}
	free(s);
	close(d->infile);
}

void	heredoc(t_data *d, int ac, char **av)
{
	if (strncmp(av[1], "heredoc", 8))
	{
		d->infile = open(av[1], O_RDONLY);
		if (d->infile == -1)
			exit_prog(d, "Infile doesn't exist\n", 1);
		d->outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (d->outfile == -1)
			exit_prog(d, "Outfile wasn't created\n", 1);
		return ;
	}
	d->heredoc = 1;
	d->hdt = ".heredoctmp";
	d->infile = open(d->hdt, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (d->infile == -1)
		exit_prog(d, "Heredoc not created\n", 1);
	d->outfile = open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (d->outfile == -1)
		exit_prog(d, "Outfile not created\n", 1);
	read_heredoc(d, av);
	d->infile = open(d->hdt, O_RDONLY);
	if (d->infile == -1)
		exit_prog(d, "Failed open infile\n", 1);
}
