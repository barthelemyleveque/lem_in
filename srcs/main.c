/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrzepec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:22:33 by anrzepec          #+#    #+#             */
/*   Updated: 2019/05/10 15:31:22 by anrzepec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		valid_graph(t_graph *g)
{
	int	*map;

	if (!g->start || !g->end)
		return (NO_IO);
	if (!(map = (int*)malloc(sizeof(int) * PRIME)))
		return (M_FAIL);
	reinit_tabs(map, PRIME);
	if (bfs_launcher(g, map) == 1)
	{
		ft_putendl("");
		free(map);
		return (1);
	}
	free(map);
	return (0);
}

int		main(int ac, char **av)
{
	int			ret;
	t_graph		graph;

	if ((ret = init_graph(&graph)) < 0)
		return (return_error(ret, &graph));
	if (!ret)
		ft_putendl("Stopped processing links after an error, \
			solving lem-in anyway ...");
	if ((ret = valid_graph(&graph)) < 1)
		return (return_error(ret, &graph));
	init_bfs(&graph);
	free_graph(&graph);
	return (0);
}