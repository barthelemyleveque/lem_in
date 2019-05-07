/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_samere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:58:43 by bleveque          #+#    #+#             */
/*   Updated: 2019/05/07 16:57:32 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** TO DO : Cleaner le bordel, gestion des free.
*/

void	print_queue(t_queue *queue)
{
	t_queue *tmp;
	int		i;

	tmp = queue;
	i = 0;
	while (tmp)
	{
		ft_printf("Queue[%d] = %s\n", i, tmp->node->name);
		tmp = tmp->next;
		i++;
	}
}

/*
** Condition d'arret du link child fait bugguer le truc dieu sait pourquoi
*/ 

int		update_all(int *map, t_queue *queue, int *v_tab, t_graph 
		*graph)
{
	t_link	*tmp_l;

	tmp_l = queue->node->links;
	while (tmp_l)
	{
		if (!(is_visited(tmp_l, v_tab, queue->node)))
		{
			if (add_to_queue(tmp_l, queue) < 1)
				return (M_FAIL);
			add_to_visited(tmp_l, v_tab);
			add_to_parent_map(queue->node, tmp_l, map);
		}
		tmp_l = tmp_l->next;
	}
	return (1);
}

/*
** On part de notre node start, on update les positions, 
** 
*/ 

int		queue_free(t_queue *queue, int **visited)
{
	t_queue *tmp;

	while (queue)
	{
		tmp = queue;
		queue = queue->next;
		free(tmp);
	}
	free(*visited);
	return (M_FAIL);
}

int		bfs_launcher(t_graph *graph, int *parent_map)
{
	int			*visited;
	t_queue		*queue;
	t_queue		*tmp;
	int			i;

	if (!(visited = (int*)malloc(sizeof(int) * graph->nb_nodes)))
		return (M_FAIL);
	i = -1;
	while (++i < graph->nb_nodes)
		visited[i] = -1;
	visited[0] = graph->start->hash;
	queue = init_queue(graph);
	while (queue && queue->node != graph->end)
	{
		if (update_all(parent_map, queue, visited, graph) < 1)
			return (queue_free(queue, &visited));
		tmp = queue;
		queue = queue->next;
		free(tmp);
	}
	i = queue ? 1 : 0;
	queue_free(queue, &visited);
	return (i);
}

/*
**  Visited_tab : savoir vite si node = visite ou non, et maj rapide
**	-->Soit on alloue une taille de PRIME pour chercher la valeur directement
**  -->ou alors de nb_nodes puis parcourir tab[0] = HASH547, tab[1] = HASH1204... 
*/ 

int		init_bfs(t_graph *graph)
{
	int			*parent_map;
	t_edmond	*edmond;
	t_path		*path;
	int			iter;

	if (!(parent_map = (int*)malloc(sizeof(int) * PRIME)))
		return (0);
	reinit_tabs(parent_map, PRIME);
	iter = 0;
	while (bfs_launcher(graph, parent_map))
	{
		iter++;
		path = get_path(graph, parent_map);
		ek_update_flux(graph, path);
		edmond = update_edmond(graph, edmond, iter);
		reinit_tabs(parent_map, PRIME);
	}
	ants_in_my_pants(graph, edmond);
	return (1);
}

/*
** remise a zero des tableaux et des visited
*/ 

void	reinit_tabs(int *map, int len_map)
{
	int		i;

	i = -1;
	while (++i < len_map)
		map[i] = -1;
}

/*
** Initialisation des structures 
*/

t_queue		*init_queue(t_graph *g)
{
	t_queue	*queue;

	if (!(queue = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	queue->node = g->start;
	queue->next = NULL;
	return (queue);
}
