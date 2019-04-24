/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_samere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:58:43 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/24 13:47:48 by bleveque         ###   ########.fr       */
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

int		update_all(t_node *pos, int *map, t_queue *queue, int *v_tab, t_graph 
		*graph)
{
	t_link	*tmp_l;

	tmp_l = pos->links;
	while (tmp_l)
	{
		if (!(is_visited(tmp_l, v_tab)))
		{
			add_to_visited(tmp_l, v_tab);
			if (!(add_to_queue(tmp_l, queue)))
				return (0);
			add_to_parent_map(pos, tmp_l, map);
		}
		if (tmp_l->child == graph->end)
		{
			ft_printf("yes\n");
			return (2);
		}
		tmp_l = tmp_l->next;
	}
	return (1);
}

/*
** On part de notre node start, on update les positions, 
** 
*/ 

int		bfs_launcher(t_graph *graph, int *visited_tab, int *parent_map)
{
	t_queue		*queue;
	t_queue		*tmp;
	t_node		*pos;
	int			ret;

	pos = graph->start;
	// on met start = visitE 
	visited_tab[0] = pos->hash;
	queue = init_queue();
	ret = 0;
	while (pos != graph->end)
	{
		if (update_all(pos, parent_map, queue, visited_tab, graph) == 2)
		{
			// FAIRE UNE FONCTION FREE QUEUE
			//print_queue(queue);
			break;
		}
		ret = (pos->name == queue->node->name) ? ret + 1 : 0;
		if (ret >= 2)
		{
			ft_printf("nada que hacer senor\n");
			return (-1);
		}
		tmp = queue;
		pos = tmp->node;
		if (queue->next)
		{
			queue = queue->next;
			free(tmp);
		}
	}
	free(queue);
	return (1);
}

/*
**  Visited_tab : savoir vite si node = visite ou non, et maj rapide
**	-->Soit on alloue une taille de PRIME pour chercher la valeur directement
**  -->ou alors de nb_nodes puis parcourir tab[0] = HASH547, tab[1] = HASH1204... 
*/ 

int		init_bfs(t_graph *graph)
{
	int			*visited_tab;
	int			*parent_map;
	int			i;

	if (!(visited_tab = (int*)malloc(sizeof(int) * graph->nb_nodes)))
		return (0);
	if (!(parent_map = (int*)malloc(sizeof(int) * PRIME)))
		return (0);
	i = -1;
	while (++i < graph->nb_nodes)
		visited_tab[i] = -1;
	bfs_launcher(graph, visited_tab, parent_map); // while il ret pas -1
	get_path(graph, parent_map);
	//reinit visited_tab();
	//ek_update_flux();
	return (1);
}

/*
** Initialisation des structures 
*/

t_queue		*init_queue()
{
	t_queue	*queue;

	if (!(queue = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	queue->node = NULL;
	queue->next = NULL;
	return (queue);
}
