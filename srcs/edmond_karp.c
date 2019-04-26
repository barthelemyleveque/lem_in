/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:49:26 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/26 14:19:30 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** closed permet lors de la recherche des chemins de ne pas passer par les memes
** liens a chaque fois || fonction degueue a revoir
*/ 

t_path		*find_new_path(t_graph *graph)
{
	t_node	*node;
	t_link	*link;
	t_path	*path;
	t_path	*tmp;
	t_path	*start;

	link = graph->start->links;
	node = graph->start;
	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	path->node = node;
	path->next = NULL;
	start = path;
	while (node != graph->end)
	{
		if ((link->child == graph->end) || (link->flow == 1 && link->closed == 0))
		{
			link->closed = 1;
			//link->child->visited = 1;
			//ft_printf("node : %s et lien vers %s is closed\n", node->name, link->child->name);
			if (!(tmp = (t_path*)malloc(sizeof(t_path))))
				return (NULL);
			tmp->node = link->child;
			node = link->child;
			tmp->next = NULL;
			path->next = tmp;
			if (link->child == graph->end)
				return (start);
			path = path->next;
			link = path->node->links;
		}
		else
			link = link->next;
	}
	return (start);
}

void	open_paths(t_graph *graph, t_path **tab_paths, int boucle)
{
	int		i;
	t_node	*follow;
	t_link 	*tmp;
	t_path	*path;

	i = 0;
	while (i < boucle)
	{
		path = tab_paths[i];
		while (path)
		{
			tmp = path->node->links;
			if (!(path->next))
			{
				//tmp->child->visited = 0;
				tmp->closed = 0;
				break ;
			}
			follow = path->next->node;
			while (tmp->child != follow)
				tmp = tmp->next;
			tmp->closed = 0;
			//tmp->child->visited = 0;
			path = path->next;
		}
		i++;
	}
}

t_edmond	*update_edmond(t_graph *graph, t_edmond *old_eddy, int boucle)
{
	t_edmond	*new;
	t_path		**tab_paths;
	t_path		*path;
	t_path		*logic_path;
	int			i;

	if (!(new = (t_edmond*)malloc(sizeof(t_edmond))))
		return (NULL);
	if (!(tab_paths = (t_path**)malloc(sizeof(t_path*) * boucle)))
		return (NULL);
	new->nb_chemin = boucle;
	new->next = (boucle > 1) ? old_eddy : NULL;
	i = -1;
	while (++i < boucle)
	{
		path = find_new_path(graph);
		ft_printf("\n ------- PATH number %d -------- \n", i);
		print_path(path);
		tab_paths[i] = path;
	}
	open_paths(graph, tab_paths, boucle);
	new->tab_paths = tab_paths;
	return (new);
}
