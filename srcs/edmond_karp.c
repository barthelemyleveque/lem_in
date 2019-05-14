/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:49:26 by bleveque          #+#    #+#             */
/*   Updated: 2019/05/10 18:15:35 by anrzepec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			update_path(t_link *link, t_path **path, t_node *node)
{
	t_path	*tmp;

	link->closed = 1;
	if (!(tmp = (t_path*)malloc(sizeof(t_path))))
		return (M_FAIL);
	tmp->node = link->child;
	node = link->child;
	tmp->next = NULL;
	(*path)->next = tmp;
	return (1);
}

int			init_path(t_path **path, t_path **start, t_node *node)
{
	if (!(*path = (t_path*)malloc(sizeof(t_path))))
		return (M_FAIL);
	(*path)->node = node;
	(*path)->next = NULL;
	*start = *path;
	return (1);
}

t_path		*find_new_path(t_graph *graph, int len)
{
	t_node	*node;
	t_link	*link;
	t_path	*path;
	t_path	*start;

	link = graph->start->links;
	node = graph->start;
	if (init_path(&path, &start, node) < 0)
		return (NULL);
	while (node != graph->end)
	{
		if ((link->child == graph->end) || (link->flow == 1 && link->closed == 0))
		{
			len++;
			if (update_path(link, &path, node) < 0)
				return (NULL);
			if (link->child == graph->end)
				break;
			path = path->next;
			link = path->node->links;
		}
		else
			link = link->next;
	}
	start->len = len;
	return (start);
}

void	open_paths(t_graph *graph, t_path **tab_paths, int boucle)
{
	int		i;
	t_node	*follow;
	t_link 	*tmp;
	t_path	*path;

	i = -1;
	while (++i < boucle)
	{
		path = tab_paths[i];
		while (path)
		{
			tmp = path->node->links;
			if (!(path->next))
			{
				tmp->closed = 0;
				break ;
			}
			follow = path->next->node;
			while (tmp->child != follow)
				tmp = tmp->next;
			tmp->closed = 0;
			path = path->next;
		}
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
		if (!(path = find_new_path(graph, 0)))
			return (NULL);
		path->nb_ants = 0;
		tab_paths[i] = path;
	}
	open_paths(graph, tab_paths, boucle);
	new->tab_paths = tab_paths;
	return (new);
}
