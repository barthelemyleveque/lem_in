/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:13:49 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/26 16:37:15 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path(t_path *path)
{
	int 	i;

	i = 0;
	while (path)
	{
		ft_printf("node num %d : %s\n", i, path->node->name);
		i++;
		path = path->next;
	}
}

t_path	*get_path(t_graph *graph, int *parent_map)
{
	int		node;
	int		introduced_by;
	t_path	*path;
	t_path	*tmp;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	node = graph->end->hash;
	path->node = graph->end;
	path->next = NULL;
	while (graph->start->hash != node)
	{
		introduced_by = parent_map[node];
		if (!(tmp = (t_path*)malloc(sizeof(t_path))))
			return (NULL);
		tmp->node = graph->tab[introduced_by];
		tmp->next = path;
		node = introduced_by;
		path = tmp;
	}
	//print_path(path);
	return (path);
}

/*
** Rajouter flow oppose dans le cas ou 1 | 1 s'annulent 
** Modifier pour avoir le lien oppose direct la on comprend R
*/

void	ek_update_flux(t_graph *graph, t_path *path)
{
	t_node	*child;
	t_link	*link_update;
	t_path	*tmp;
	t_link	*link_opp;
	
	while (path->next)
	{
		child = path->next->node;
		link_opp = path->next->node->links;
		link_update = path->node->links;
		while (child != link_update->child)
			link_update = link_update->next;
		while (path->node != link_opp->child)
			link_opp = link_opp->next;
		if (link_opp->flow == 1)
		{
			link_opp->flow = 0;
			link_update->flow = 0;
		}
		else
			link_update->flow = 1;
		//ft_printf("parent [%s] to child [%s] flow = %d closed : %d\n", path->node->name, link_update->child->name, link_update->flow, link_update->closed);
		//ft_printf("parent [%s] to child [%s] flow = %d closed : %d \n\n", path->next->node->name, link_opp->child->name, link_opp->flow, link_opp->closed);
		tmp = path;
		path = path->next;
		free(tmp);
	}
}
