/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 23:15:06 by andrewrze         #+#    #+#             */
/*   Updated: 2019/05/10 01:38:19 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_graph(t_graph *g)
{
	int		i;
	t_link	*tmp;
	t_link	*tracer;

	i = -1;
	while (++i < PRIME)
	{
		if (g->tab[i])
		{
			tracer = g->tab[i]->links;
			while (tracer)
			{
				tmp = tracer;
				tracer = tracer->next;
				free(tmp);
			}
			ft_strdel(&(g->tab[i]->name));
			free(g->tab[i]);
		}
	}
	free(g->tab);
}

int		return_logic_error(int err, t_graph *g)
{
	if (err == END_ERROR)
		ft_putendl("Duplicate ##end.");
	if (err == START_ERROR)
		ft_putendl("Duplicate ##start.");
	if (err == NO_IO)
		ft_putendl("Missing ##start or ##end.");
	free_graph(g);
	return (1);
}

int		return_error(int err, t_graph *g)
{
	if (err > -7)
	{
		if (!err)
			ft_putendl("No path from ##start to ##end: Invalid Graph.");
		if (err == M_FAIL)
			ft_putendl("malloc() error.");
		if (err == O_FAIL)
			ft_putendl("open() error.");
		if (err == A_FAIL)
			ft_putendl("Number of ants is invalid.");
		if (err == NODE_ERROR)
			ft_putendl("Node input is invalid.");
		if (err == NODE_ERROR_NAME)
			ft_putendl("Node name can't start with 'L'.");
		if (err == NODE_ERROR_CORD)
			ft_putendl("Node coordinates must be of type int.");
		free_graph(g);
		return (1);
	}
	return (return_logic_error(err, g));
}
