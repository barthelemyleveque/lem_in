/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_samere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:58:43 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/23 17:44:25 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_to_visited(t_link *link, int *tab)
{
	int		i;

	i = 0;
	while (tab[i] != -1)
		i++;
	tab[i] = link->child->hash;
	ft_printf("Visited | %d\n", tab[i]);
}

int		add_to_queue(t_link *link, t_queue *queue)
{
	t_queue	*tmp;
	t_queue *add;

	if (!(queue->node))
	{
		queue->node = link->child;
		return (1);
	}
	if (!(add = (t_queue*)malloc(sizeof(t_queue))))
		return (0);
	add->node = link->child;
	add->next = NULL;
	tmp = queue;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
	ft_printf("QUEUE | tmp : %d tmp->next : %d\n", tmp->node->hash, tmp->next->node->hash); 
	return (1);
}

int		add_to_parent_map(t_node *pos, t_link *link, t_parent *map)
{
	t_parent	*tmp;
	t_parent	*add;

	if (map->h_node == -1)
	{
		map->h_introby = pos->hash;
		map->h_node = link->child->hash;
		ft_printf("parent | node : [H%d] intro par : [H%d]\n", map->h_node, map->h_introby); 
		return (1);
	}
	if (!(add = (t_parent*)malloc(sizeof(t_parent))))
		return (0);
	add->h_introby = pos->hash;
	add->h_node = link->child->hash;
	add->next = NULL;
	tmp = map;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
	ft_printf("parent | node : [H%d] intro par : [H%d]\n", add->h_node, add->h_introby); 
	return (1);
}

/*
** Ne regarde pas seulement si le lien est visite, mais check si une fourmi
** peut prendre le chemin
*/

int		is_visited(t_link *link, int *tab)
{
	int	i;

	if (link->flow == 1 || link->flow == -2)
		return (1);
	i = 0;
	while (tab[i] != -1)
	{
		if (tab[i] == link->child->hash)
			return (1);
		i++;
	}
	return (0);
}


int		update_all(t_node *pos, t_parent *map, t_queue *queue, int *v_tab)
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
			if (!(add_to_parent_map(pos, tmp_l, map)))
				return (0);
		}
		tmp_l = tmp_l->next;
	}
	return (1);
}

/*
** Initialiserles valeurs de queue et map avant parce que c cheum sa mere
** 
*/ 

int		bfs_launcher(t_graph *graph, int *visited_tab)
{
	t_parent	*parent_map;
	t_queue		*queue;
	t_node		*pos;

	pos = graph->start;
	// on met start = visite accent aigu sur le
	visited_tab[0] = pos->hash;
	if (!(queue = (t_queue*)malloc(sizeof(t_queue))))
		return (0);
	queue->node = NULL;
	queue->next = NULL;
	if (!(parent_map = (t_parent*)malloc(sizeof(t_parent))))
		return (0);
	parent_map->h_node = -1;
	parent_map->h_introby = -1;
	parent_map->next = NULL;
	while (pos != graph->end)
	{
		update_all(pos, parent_map, queue, visited_tab);
		if (queue == NULL)
			return (-1);
		//pos = update_pos(queue);
		pos = graph->end;
	}
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
	int			i;

	if (!(visited_tab = (int*)malloc(sizeof(int) * graph->nb_nodes)))
		return (0);
	i = -1;
	while (++i < graph->nb_nodes)
		visited_tab[i] = -1;
	bfs_launcher(graph, visited_tab); // while il ret pas -1
	//ek_update_flux();
	return (1);
}
