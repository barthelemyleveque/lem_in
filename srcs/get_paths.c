/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:13:49 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/24 15:37:09 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_path(t_graph *graph, int *parent_map)
{
	int		node;
	int		introduced_by;

	node = graph->end->hash;
	while (graph->start->hash != node)
	{
		introduced_by = parent_map[node];
		ft_printf("%s introduced by %s\n", graph->tab[node]->name, graph->tab[introduced_by]->name);
		node = introduced_by;
	}
}
